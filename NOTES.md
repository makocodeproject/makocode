MakoCode Specification (draft):
- The matrix code contains the following sections in order:
    - Address section
        - Address size and size-size Payload
            - Consists of two separate values that determine the fixed address size used in the rest of the address section.
            - Always starts at address 0
            - Value 0: Address size-size
                - Starts with a fixed 2 bits indicating the fixed size of the actual address size, by adding 3 to this value.
                - For example, a value of 0b10=2 means we use 2+3=5 bits in the address-size.
                - Minimum value 0, or 3 address-size bits, and maximum value 3, or 6 address-size bits.
            - Value 1: Address size
                - Using the number of bits in the first value, determines how many bits are used for the address indices later in this section.
                - The actual address size is 6 plus the value of the address size.
                - Minimum address size is 0b000=0, given an address size-size of 0, meaning that this matrix code can address at least 2^6 bits.
                - Maximum value is 0b111111=63 with address size-size of 3, meaning that this matrix code can address at most ~2^69 bits, or 512 exabytes.
                - The current implementation will support only 2^64 bits. More could be supported with big integers.
            - The values will be as small as is possible, e.g. the address-size is ceiling(log2(entire matrix code size in bits + 1)) - 6
        - Address index Payload
            - The starting address of each region of the file after the address index, uncompressed.
            - There are always 8 entries:
                - Address size and size-size ECC
                - Address index
                - Address index Hash
                - Address index ECC
                - Metadata section
                - Fiducial data section
                - Data section
                - The bit after the end of the entire matrix code
        - Address size and size-size Hash
            - Always starts at a constant address determined by address size and size-size: (2) + (address size-size + 3) + (8 * (address size + 6))
        - Address size and size-size ECC
        - Address index Hash
        - Address index ECC
    - Metadata section
        - Metadata address subsection
            - Metadata key size-size of 2 bits. Add 1 to get metadata key size.
            - Then size bits plus 6 to get metadata key/value pair bits.
            - Then the actual exact number of metadata entries using that many bits.
            - Examples:
                - Minimum/default: size-size 0b00=0, size 0b0, a special value indicating that there will be no key values included
                    - Metadata will start from Value 0 and increment by exactly 1, without skipping any entries.
                    - Without this, the keys take up to 75*7 extraneous bits of information, which is less than just including every metadata entry, possibly with size 0 for many.
                - Size-size 0b00=0, size 0b1, thus 7 bits for metadata key, up to 2^7=128 metadata key/value pairs.
                - Maximum: size-size 0b11=3, size 0b1111=15, thus 21 bits for metadata key, up to 2^21, ~2 million metadata key/value pairs.
            - Then addresses for each metadata key start
                - Uses a custom address size: ceiling(log2(size of the metadata key/value pair section + 1)) that starts at the second key/value pair, and ends 1 bit after the last.
        - Metadata key/value pairs
            - Can have custom key value pairs defined by the user as well. There are currently 75 predefined values.
            - Most predefined keys consist of 3 values: Value Payload, Value Hash, and Value ECC
            - Each key should be in numerical ascending order. This helps to binary search for any arbitrary given key in logarithmic time.
            - Predefined keys as follows:
                - Value 0: Metadata address Hash
                - Value 1: Metadata address ECC
                - Value 2: Metadata overall Hash
                    - Includes the entire section, with metadata address table and all keys/values
                - Value 3: Metadata overall Error correction
                    - Includes the entire section, with metadata address table and all keys/values
                - Values 4-6: Encoder semantic version
                    - Includes the major, minor, and revision version of the encoder at the time of writing. Each version uses exactly one-third of the address space designated.
                - Values 7-9: Page count
                - Values 10-12: Dimensions
                    - A pair of values, pageHeightDots and then pageWidthDots of the data on each page measured in dots. Each value will take exactly half of the address space designated.
                - Values 13-15: Dot fill coverage
                    - 3 fixed bits for dot fill coverage size-size. Add 2 to get size.
                    - Then size bits plus 1 to get digit bits.
                    - Two digits of dot fill coverage size, numerator and denominator, giving the percentage of each dot filled with the colored pixels, and the rest filled by the background pixels.
                    - Example: Size-size 0b010=2, size 0b100=4, numerator=3, denominator=4. Thus each dot is actually 4x4 pixels, with 3x3 pixels as the color (e.g. black), and the rest as the background (e.g. white).
                - Values 16-18: Shade/intensity states
                    - It may work if the printer supports high-quality half-toning or dithering, where dots can have an intensity smaller than the highest resolution would imply.
                    - Starts with 3 bits designating shade state size-size. Add 1 to the given value to get size.
                    - Then size bits plus 2 to get shade states.
                    - Bits recoverable per pixel is equal to log2(shade states)
                    - Examples
                        - Size-size 0, size 0 (default/minimum): 2 shade states, 0% and 100% (1 bit/pixel)
                        - Size-size 1, size 2: 4 shade states, 0%, 33.33%, 66.66%, 100% (2 bits/pixel)
                        - Size-size 7, size 255 (maximum): 257 shade states (~8.006 bits/pixel)
                - Values 19-21: Color states
                    - Starts with 3 bits for color state size-size. Add 1 to get size.
                    - Then size bits plus 2 to get color states.
                    - Examples:
                        - Size-size 0b000=0, size 0b0=0, 2 states (minimum/default, such as black and white)
                        - Size-size 0b001=1, size 0b11=3, 5 states (such as white, cyan, magenta, yellow, black)
                        - Size-size 0b111=7, size 0b11111111=511, 513 states (maximum)
                - Values 22-24: Color mode
                    - Value 0: Color Mask
                        - This may work better for standard half-tone printing with screen angles.
                        - The matrix code will be masked (matrix code value AND color-state) with the given colors, and thus each color will be read as a totally separate page. Each page can have a different angle and other characteristics.
                        - Bits recoverable per pixel is equal to states
                        - For the 4 state example below, value of 10010011, the first "page" would be 10, or white black, the second "page" would be 01, or black cyan, 3rd 00 or black black, 4th 11 or yellow yellow. This assumes the screen angles allow the bits to be independently readable.
                    - Value 1: Color Compression
                        - This may work better for spot printing, where unrelated colors are supplied.
                        - The first 2^floor(log2(states)) states will encode floor(log2(states)) bits. These will take lower precedence.
                        - The next states will encode floor(log2(states)) + 1 bits, starting from 0 and counting up. These will take higher precedence.
                        - Data will be 0-padded at the end if the minimum state is larger than the remaining data. This only occurs for the very last pixel of the file. The address table's final entry will indicate where the proper end lies, so essentially the 0-suffix is junk data. We will likely add fiducial/ECC/Hash bits to make sure this doesn't happen intentionally.
                        - With a non log2 number of bits, we cannot read shuffled data out of order, which may slow down decoding significantly.
                        - Bits recoverable per pixel is equal to log2(states)
                        - For the 5 state example of WCMYB below, replace the input data as follows:
                            - White: 00
                            - Cyan: 01
                            - Magenta: 10
                            - Yellow: 11
                            - Black: 000
                            - Thus the data 1001000001 would be written: Magenta, Cyan, Black, White, Magenta (0-padded)
                - Values 25-27: Colors
                    - Starts with 3 bits for colors size-size. Add 1 to this value to get size.
                    - Then size bits plus 1 to get colors.
                    - Examples:
                        - Size-size 0b000=0, size 0b0=0, so 1 bit per each of RGB, or 3-bits overall.
                        - Size-size 0b010=2, size 0b111=7, so 8 bits per each of RGB, or 24-bits overall.
                        - Size-size 0b111=7, size 0b11111111=511, so 512 bits per each of RGB.
                    - Then for each state, the bits for each of Red, Green, and Blue, specifying which color is used for the given value read/written on the matrix code
                        - For example, with 3-bits and 2 states, useful for white and non-black printing (1 bit/pixel):
                            - 0b111 (Value 0: White)
                            - 0b000 (Value 1: Cyan)
                        - For example with 3-bits and 24 states, useful for color mask (2 bits/pixel)
                            - 0b111 (Value 0: White)
                            - 0b011 (Value 1: Cyan)
                            - 0b101 (Value 2: Magenta)
                            - 0b110 (Value 3: Yellow)
                        - For example with 3-bits and 25 states, useful for color compression (~2.3 bits/pixel):
                            - 0b111 (Value 0: White)
                            - 0b011 (Value 1: Cyan)
                            - 0b101 (Value 2: Magenta)
                            - 0b110 (Value 3: Yellow)
                            - 0b000 (Value 4: Black)
                - Values 28-30: Color Screen Angles
                    - Provide one screen angle per color, to handle this common printer setting. Dots will be printed at an angle per each color.
                    - Starts with 4 fixed bits for size-size. Add 1 to get the size bits.
                    - Then size bits plus 1 to get the number of digits.
                    - Two digits per color, numerator and denominator, which divided gives the fraction of 360 degrees to rotate counter-clockwise of 0 degrees (pointing to the right).
                    - Note 0 and 1 are always equal. Add 1 to denominator, as it cannot be 0.
                    - Example:
                        - Size-size 0b0000=0, size=0b0, 1-bit per color screen angle. A value of 0 or 1 only.
                            - Numerator 0, denominator 0 is 0/1, or 0 degrees rotation.
                            - Numerator 1, denominator 1 is 1/2, or 180 degrees rotation.
                        - Size-size 0b0011=3, size=0b1000=8, so we can specify 9-bits per angle. For 5 color states WCMYB:
                            - 0, 359: 0/360, 0 degrees rotation (White)
                            - 15, 359: 15/360, 15 degrees rotation (Cyan)
                            - 75, 359: 75/360, 75 degrees rotation (Magenta)
                            - 0, 359: 0/360, 0 degrees rotation (Yellow)
                            - 45, 359: 45/360, 45 degrees rotation (Black)
                        - Size-size 0b1111=15, size=0b1111111111111111, so we can specify up to 1/131072 of a circle, or ~1/364 of a degree.
                - Values 31-33: Mask mode
                    - Value 0: No mask mode.
                    - Value 1: XOR matrix code with alternating 0 and 1.
                    - Value 2: XOR matrix code with PCG-64 seed-0.
                - Values 34-36: Data shuffle mode
                    - Value 0: No shuffling. Data is written per page, in English reading order, e.g. starting from top left, going right, then continuing down, ending at bottom right.
                    - Value 1: Fisher-yates shuffle with PCG-64 seed-0. The algorithm proceeds forward, so finding the expected location of the first bits, likely including the fiducial data, is very fast. Page order is shuffled using seed-0. The position on each page is shuffled using a seed of page-number. Thus, fiducial data, per-page-hash, or other per-page data can be spread equally across pages by making it a multiple of number of pages. Otherwise, it would have a normal distribution and some pages would be harder to read. Each page has a different shuffled order, which makes it more resilient to physical damage.
                - Values 37-39: Non-Data Compression
                    - Value 0: No compression
                    - Value 1: LZMA Compression of individual atomic values within address table, encoder data, metadata, except for address size-size.
                        - E.g. Each address index is compressed individually, each encode subsection is compressed individually, each metadata value is compressed individually. As each field is small, will not be much compression in general, but may have faster decoding as fewer values need to be read before backtracking.
                    - Value 2: LZMA Compression of overall address table, encoder data, metadata, except for the address size-size.
                        - E.g. Maximum compression of everything. Will have a better compression ratio, but much slower decoding/backtracking as everything will need to be read in first before determining any individual uncompressed value. Streaming compression mitigates this.
                - Values 40-42: Error correction
                    - Value 0: Reed Solomon.
                        - Can eventually mark pixels closest to threshold (least certain of their value) as erasures, which will improve the error detection rate. Chunk data into blocks of 2^8, though maybe different for region mapping.
                - Values 43-45: Hash Algorithm
                    - Value 0: Rabin-Karp rolling hash, base-2 (per bit), then with bitwise not.
                        - Bitwise not helps the case where small values, mostly 0's, are then matched with erroneous whitespace. Allows for sequential bits to be computed on the fly, and then efficiently rolled back during backtracking. Given a size N, the number of bits dedicated for the Hash, we will find the largest prime modulo that can fit. We will use a sieve to generate it, but will provide precalculated values up to ~2^64. Note that CRC bits should generally be greater than log2(size of data). Thus precalculating up to 256 is also technically possible to be used, given the maximum file size.
                - Values 46-48: Fiducial data mode
                    - Value 0: PCG-64 seed-0.
                - Values 49-51: Data compression mode
                    - Value 0 or missing: No compression
                    - Value 1: LZMA
                - Values 52-54: Data encryption mode
                    - Value 0 or missing: No encryption
                    - Value 1: AES + Twofish + Serpent chained
                    - Value 2: AES (Rijndael)
                    - Value 3: Twofish
                    - Value 4: Serpent
                - Values 55-57: Signature mode
                    - Value 0 or missing: No signature
                    - Value 1: GPG signature. Can help determine if data was tampered with, or also to verify authenticity if giving the code to someone else.
                - Values 58-60: Data multiple file mode
                    - Value 0 or missing: Single file
                    - Value 1: Tar
                - Values 61-63: Special page mode
                    - Value 0: Not a settings page. The data section consists of regular user data
                    - Value 1: Encoder settings page. The data section consists of encoder settings specifically optimized for the printer/scanner/computer combination. This is usually printed at a much lower density, and dramatically speeds up decoding if present. Usually printed a few times, physically interleaved and also placed on the outside to protect the inner data. Also usually comes along with pretty-print text of everything on the same page, and a description of how to use this matrix code.
                    - Value 2: File page. The data section consists of the address table, metadata, hash, and encoder settings for a specific single file. Along with above explanation, can print text for file size and hash/ecc rates.
                - Values 64-66: Date of creation (milliseconds since epoch)
                - Values 67-69: Metadata text encoding. Determines the text encoding of metadata values, such as filename or user defined notes.
                    - Value 0: ASCII
                    - Value 1: UTF-8
                - Values 70-72: Filename
                - Values 73-75: User defined notes, e.g. a description of the file
    - Fiducial section
        - Uses pre-determined data, so there is no need for a Hash or ECC section here.
        - Speeds up decoding as a form of predictable fiducial marking, especially when using data shuffling.
        - Can help to figure out the given page number for page-out-of-order fixing when using data shuffling, as the per-page data will usually have a predictable pattern.
        - Separate from metadata because it will potentially be very large, and can add unnecessary bits to the metadata address index.
        - Usually used to pad data to fill up the last page. This is not covered in metadata, as the encoder will simply expand the fiducial data via address section. However, the command line option may provide a zero-padding option instead.
    - Data section
        - The actual body of data intended to be encoded by the data matrix.
        - Starts with 2 addresses of length address-size
            - Where the Hash starts
            - Where the ECC starts
        - Then followed by the Data Payload, Hash, and ECC.

Decoding algorithm basics (draft):
- All decoding parameters can be modified. Reasonable defaults will be determined. To get better eventual decoding, decoding will backtrack if a certainty threshold is not met at different points. We will usually search outward in a linear pattern on each side of the default value by the smallest increment.
- Assume that the data appears essentially random on page. Data is rectangular.
- General algorithm:
    - Guess color depth by running a threshold of each channel. Guess shading bits are 1 by default.
    - Run a histogram over the entire image. Starting from the middle gray value, walk outward until a local minimum is found. This will be referred to as the global-histogram-minimum, which should be the overall best starting guess for determining white vs black.
    - The maximum on either end is the usually black pixel and usually white background color.
    - Search for any boundary: Starting from the top-right corner of the image, calculate a moving average with a local window, which can be efficiently moved by 1 pixel in linear time, by adding in the new boundary line and removing the old boundary line. If the window is partially outside the image, those values are considered white. Walk the window to center at each pixel, and note any pixels where the average is within a percentage of the global-histogram-minimum.
    - Refine boundaries: Take each left-most, right-most, top-most, and bottom-most point and calculate a local window with a histogram minimum and moving average. Walk those points outwards until the average is greater than the minimum, meaning a local boundary has been found. Remove the point from consideration, add it to the refined boundaries list, and continue until all points have been processed. This helps when the image has fading.
    - Using each border point's nearest neighbor, calculate the slope and y-intercept. Take the 4 largest clusters of slopes/y-intercepts to calculate the likely 4 border lines. For any point close enough to a border line, use it to calculate a polynomial fit line for the 4 borders. The intersection of the fit lines will yield four boundary points.
        - The image could have hard-to-recover boundaries, for example if the entire boundary has been erased or smudged. We could still recover the data within, but only by randomly brute-force guessing an orientation. Possibly the matrix code-pixel orientation could be used as well to guess this.
    - Guess an overall orientation of 0 degrees. There is also 90, 180, or 270 degrees.
- Determine grid step for each pixel: Starting from a corner pixel, get the horizontal and vertical grid step of the given pixel. Determine a local window moving average and histogram minimum. Using horizontal and vertical lines starting with the known angle of the border fit-lines. When the value shifts from black to/from white, assume this is the correct grid step. Optimize the angle by looking for where its calculated histogram max and min value are least (e.g. the line contains mostly gray boundary) - this doesn't work for black/white scans though.
- Halfway between the grid boundary should be the center, but it could also be shifted at each location. Can start with what appears to be a local peak max or min value. The pixel can use a weighted average of values starting from the center.
- DFS towards ECC, Hash, or fiducial data on each page along with a known ECC rate and threshold for failures seen. Decoding can backtrack if the data will not likely be recoverable (e.g. too much fiducial data is wrong). Between correct fiducial data, we can guess clipping, folding, erasures, dirt, noise, smudging, and other errors once enough fiducial data is obtained to be confident we're actually looking at the matrix code. Can use Needleman-Wunsch to figure out the best alignment for some of these.

Implementation notes (draft):
- Uses the GNU AGPLv3 license
- Language: C++ for the encoder and decoder. May use Python for prototyping or helper scripts.
- Code must be completely self-contained, meaning that any library function must be copied in locally as a fork, even stdlib. Possibly can use git submodules where possible, though hand copying and minifying/shrinking will provide the smallest and most stable result.
- Dependencies
    - C++ draft specification: https://github.com/cplusplus/draft/tree/main/source
    - Encryption: Veracrypt
    - Random: Boost or stdlib
    - Unit testing: Boost
    - Reed Solomon: libcorrect
    - LZMA compression/TAR: libarchive
    - GPG: GnuPG
    - Linter: Clang-tidy
- Image format: Portable PixMap (PPM) only, ASCII with 8 bits per color, e.g. 24-bits per pixel. ImageMagick or other will be needed to convert between formats. A simple external script can be provided as a suggestion.
- Metadata is output as a json file. Use an external script to merge metadata json output with data, e.g. to change the file settings in the OS.
- Ambiguity: Due to brute-force guessing, data can be ambiguous if Hash or ECC is too small or not supplied. This occurs even without physical damage. Thus brute-forcing cannot just return the first correct result, but must return all possible correct results, of which there may be many. We must modify input parameters to ensure that the subsequent results are different - we can Hash the entire output and add to a set in decoding to quickly verify this. Command line can limit from 1 to infinity as well.
- Calibration program that prints calibration pages, then scanned in to automatically determine the best settings (e.g. high-density slow-decoding, balanced, low-density fast-decoding). Simply print seed-0 pseudorandom data in plain, which is quick to decode. Keep printing in higher density, possibly binary searching, to find maximum data density for this printer/scanner/computer combination, with no time limit.
- Alternately, a questionnaire to figure out the best ECC settings. Note that a faster computer can brute-force faster, and a time-limit may be set.
- Page equality
    - Unequal page sizes are not supported. Partial pages are not supported.
    - By default, pad with extra fiducial/Hash/ECC bits so that there isn't junk data at the end.
    - If pages need to be unequal, the user could always split their data manually and print a separate file per page size - or just use the smallest one.
- Tool to generate source code print - base decoder is in text, compression in uncompressed code, and everything else in compressed code. Compact option to just print full schema description, with all source in compressed code. Also print out g++ implementation in C++, and C++ ISO spec (latex draft). Minify and shrink all source code before printing and whitelist what goes in, possibly condense licensing into a summarized file with license type and name.
- Can write an optional header/footer on each page describing the filename and page number, possibly even some encoding settings and other metadata, filesize/ecc rate, etc.
- Run physical tests, check different printer/scanner/computer combinations and paper/film mediums. Leave data for a while, artificially age, different storage conditions, etc. Post findings.
- Decoder debug option to print out debug images/logs for each decoding step
- Executable should be standalone/static, strip/compress it
- Fork all dependencies recursively into GitHub account and submodule from them.
- Aim for backwards compatibility in each version, keep a list of supported options per version.
- Aim to rewrite all dependencies internally over time.
- Fun: Script to create art in output that is actually readable. Possibly just apply matrix code steganographically to an input image.