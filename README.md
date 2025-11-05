# Parallel File Compressor (PFC)

A high-performance C++ file compression utility that leverages **OpenMP** for parallel processing to compress and decompress files significantly faster than sequential approaches.

## Features

✓ **Parallel Compression & Decompression** - Utilizes multi-core processors with OpenMP  
✓ **Automatic Thread Detection** - Dynamically detects and uses optimal number of CPU cores  
✓ **Custom Binary Format** - Efficient .pfc format with metadata and chunk indexing  
✓ **Performance Benchmarking** - Built-in sequential vs parallel comparison tool  
✓ **Progress Tracking** - Real-time progress display for compression operations  
✓ **Comprehensive Error Handling** - Robust error detection and reporting  
✓ **Detailed Statistics** - Compression ratio, throughput, and thread information  

## Architecture

\`\`\`
┌─────────────────────────────────────────────────────────┐
│                  Command Line Interface                 │
│                      (main.cpp)                         │
└────────────┬────────────────────────────────────────────┘
             │
    ┌────────┴────────┬──────────────┬─────────────┐
    │                 │              │             │
    ▼                 ▼              ▼             ▼
┌─────────┐    ┌────────────┐  ┌──────────┐  ┌─────────┐
│Compress │    │Decompress  │  │Benchmark │  │ Utils   │
│ (OpenMP)│    │ (OpenMP)   │  │(Timing)  │  │(Helpers)│
└────┬────┘    └─────┬──────┘  └──────────┘  └─────────┘
     │               │
     └───────┬───────┘
             ▼
    ┌────────────────────────┐
    │   zlib Compression     │
    │ (LZ77 + Huffman)       │
    └────────────────────────┘
\`\`\`

### File Structure

\`\`\`
.
├── CMakeLists.txt              # Build configuration
├── include/
│   ├── compressor.hpp          # Compression engine
│   ├── decompressor.hpp        # Decompression engine
│   ├── benchmark.hpp           # Performance testing
│   └── utils.hpp               # Utilities and metadata
└── src/
    ├── main.cpp                # CLI entry point
    ├── compressor.cpp          # Compression implementation
    ├── decompressor.cpp        # Decompression implementation
    ├── benchmark.cpp           # Benchmark implementation
    └── utils.cpp               # Utility implementations
\`\`\`

## .pfc File Format

The custom Parallel File Compressor format stores:

\`\`\`
[Header]
├─ Magic Number (4 bytes): "PFC1" (0x50464331)
├─ Version (4 bytes): 1
├─ Original File Size (8 bytes)
├─ Number of Chunks (4 bytes)
├─ Algorithm ID (4 bytes): 0 = zlib
├─ Original Filename (256 bytes)
├─ Chunk Offsets (8 bytes × num_chunks)
├─ Chunk Sizes (4 bytes × num_chunks)
└─ Compressed Data Chunks
\`\`\`

## Building

### Prerequisites

- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake 3.10+
- OpenMP development library
- zlib development library

### On Linux/macOS

\`\`\`bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install cmake libomp-dev zlib1g-dev

# Or (macOS with Homebrew)
brew install cmake libomp zlib

# Build
mkdir build && cd build
cmake ..
make -j$(nproc)
\`\`\`

### On Windows (MinGW)

\`\`\`bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
mingw32-make -j%NUMBER_OF_PROCESSORS%
\`\`\`

## Usage

### Compress a File

\`\`\`bash
./pfc --compress input.txt                  # Creates input.txt.pfc
./pfc --compress data.bin archive.pfc       # Custom output filename
./pfc --compress large.iso output.pfc --threads 8  # Specify threads
\`\`\`

### Decompress a File

\`\`\`bash
./pfc --decompress archive.pfc              # Restores original filename
./pfc --decompress archive.pfc output.txt   # Custom output filename
./pfc --decompress archive.pfc --threads 4  # Use 4 threads
\`\`\`

### Run Benchmark

\`\`\`bash
./pfc --benchmark largefile.iso             # Auto-detect threads
./pfc --benchmark data.bin --threads 8      # Benchmark with 8 threads
\`\`\`

## Performance Example

For a 1GB test file on an 8-core system:

\`\`\`
Sequential (1 thread):     12.34 seconds
Parallel (8 threads):      2.15 seconds
Speedup:                   5.74x
Parallel Efficiency:       71.8%

Original Size:             1.00 GB
Compressed Size:           420 MB
Compression Ratio:         58.0%
Throughput:                465 MB/s
\`\`\`

## How It Works

1. **Input Analysis** - File size is determined to calculate optimal chunk count
2. **Chunk Division** - File is split into N chunks (where N = available threads)
3. **Parallel Compression** - Each thread compresses its chunk independently using zlib
4. **Metadata Creation** - Header stores original filename, size, chunk offsets, and sizes
5. **File Output** - Chunks are written sequentially with metadata header
6. **Decompression** - Metadata is read, chunks are decompressed in parallel, and reassembled

## Advanced Options

### Custom Thread Count

Override automatic detection:

\`\`\`bash
./pfc --compress file.txt --threads 16
./pfc --decompress file.pfc --threads 4
\`\`\`

### Chunk Optimization

Modify `CHUNK_SIZE` in `compressor.hpp` for different workloads:
- Smaller chunks: More parallelism but more overhead
- Larger chunks: Less parallelism but better cache efficiency

## Error Handling

The program handles:
- Missing or unreadable input files
- Permission errors on output
- Corrupted .pfc files
- Insufficient disk space
- Invalid thread counts
- zlib compression failures

All errors are reported with descriptive messages.

## Performance Tuning

1. **Thread Affinity** - Ensure threads are bound to physical cores
2. **NUMA Systems** - Pin threads to local NUMA nodes for large-scale systems
3. **Memory** - Monitor memory usage; reduce chunk count if needed
4. **I/O** - Use fast SSDs for best throughput results

## Limitations

- Maximum file size: 2^63-1 bytes (theoretical)
- .pfc files are not compatible with standard gzip format
- Thread count should not exceed available CPU cores for best performance

## Future Enhancements

- [ ] Streaming compression for very large files
- [ ] Multiple compression algorithm support (LZMA, Brotli)
- [ ] Incremental backup feature
- [ ] GPU-accelerated compression
- [ ] Network compression transfer
- [ ] Encrypted archive support
- [ ] Archive creation (.pfc as archive format)

## License

Open source for educational and professional use.

## Author

Parallel File Compressor - Educational Project

---

**Last Updated**: 2024  
**C++ Standard**: C++17  
**Build System**: CMake 3.10+
