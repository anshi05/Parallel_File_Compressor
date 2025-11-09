# Parallel File Compressor - GUI Edition

A high-performance parallel file compression and decompression tool with a modern Qt 6 desktop GUI.

## Features

### Core Compression
- Multi-threaded parallel compression using zlib
- Adaptive chunk sizing for optimal performance
- Real-time progress tracking per thread
- Benchmarking: Compare sequential vs parallel performance

### GUI Features
- Intuitive file selection with drag-and-drop support (optional)
- Real-time progress bars showing compression status
- Live statistics dashboard:
  - File size (original vs compressed)
  - Compression ratio percentage
  - Speedup factor (sequential vs parallel)
  - Time elapsed
- Performance graphs using Qt Charts
- Embedded logs console with timestamped messages
- Metadata viewer for `.pfc` file headers
- Splash screen with initialization progress
- About dialog with system information

### Threading Model
- Worker threads isolate GUI from blocking operations
- Qt signal/slot architecture for thread-safe communication
- QThread-based worker pool for compression/decompression tasks

## Building

### Prerequisites
- Qt 6.2+ (Core, Gui, Widgets, Charts)
- CMake 3.10+
- zlib development libraries
- OpenMP support

### Build Instructions

\`\`\`bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build GUI application
make pfc-gui

# Run the application
./pfc-gui
\`\`\`

## Usage

### Compression
1. Select an input file using "Browse..."
2. Choose an output file path (will create `.pfc` file)
3. Adjust thread count (defaults to CPU core count)
4. Click "Compress" and monitor progress

### Decompression
1. Select a `.pfc` file as input
2. Choose output file path for decompressed data
3. Click "Decompress" to restore original file

### Benchmarking
1. Select an input file
2. Click "Benchmark" to compare performance
3. View results in the Dashboard tab

## Architecture

### Components

**MainWindow** - Central application window managing UI and worker coordination

**ProgressDashboard** - Real-time statistics and performance visualization
- Displays compression metrics
- Charts for performance comparison
- Statistics panels for file sizes and ratios

**LogsPanel** - Dual-panel logging and metadata viewer
- Timestamped operation logs
- Metadata extraction from `.pfc` headers

**Worker Threads**
- `CompressionWorker` - Handles file compression
- `DecompressionWorker` - Handles file decompression  
- `BenchmarkWorker` - Runs performance benchmarks

### Backend Integration

The GUI layer calls existing C++ backend classes:
- `Compressor` - Core compression engine
- `Decompressor` - Core decompression engine
- `Benchmark` - Performance analysis
- `Utils` - Utilities and progress tracking

## Performance

- Utilizes all available CPU cores automatically
- Memory-efficient chunk-based processing
- Typical speedup: 3-7x on quad-core systems
- Compression ratio: 40-60% for text files

## Optional Enhancements

Future versions could include:
- Drag-and-drop file support
- Dark/light theme toggle
- Compression algorithm selection
- Advanced scheduling options
- Network transfer integration
