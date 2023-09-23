# molecular-util
Collection of utility classes used by other molecular components

## Classes

### Math

- `AxisAlignedBox`: Data structure commonly used for visibility detection
- `Math`
- `Matrix`: Matrix template
- `Matrix3`
- `Matrix4`
- `Quaternion`: 3D rotation representation
- `SphericalHarmonics`: A mathematical concept used for lighting calculations
- `Vector`: Vector template
- `Vector3`: Three-dimensional float vector
- `Vector4`: Four-dimensional float vector

### File Formats

- `DdsFile`: DDS compressed texture file
- `KtxFile`: KTX compressed texture file
- `ObjFile`: Wavefront OBJ mesh file
- `ObjFileUtils`: Utilities for OBJ files

### Threading

- `AtomicCounter`: Thread-safe, lock-less increment/decrement variable
- `GcdTaskDispatcher`
- `StdTaskQueue`
- `StdThread`
- `Task`
- `TaskDispatcher`

### File I/O

- `FileStreamStorage`
- `HostStream`
- `LittleEndianStream`
- `MemoryStreamStorage`
- `ReadStream`: Abstract base class for data storage streams
- `StreamStorage`
- `TextStream`

### 3D Data Handling

- `BufferInfo`: Information about vertex attribute data in a GPU buffer
- `CharacterAnimation`: Skeletal animation with custom file format
- `FloatToHalf`: Create 16-bit floats
- `GlConstants`: Most OpenGL constants, properly namespaced
- `Mesh`: Container for 3D mesh data
- `MeshUtils`: Various processing functions for 3D meshes
- `PixelFormat`: enum for various image data formats, mostly for use with OpenGL

### Various

- `Blob`: Holds binary data. Contents are not initialized. Movable, non-copyable.
- `CommandLineParser`: Easy processing of argc and argv
- `Hash`: Compile-time MurmurHash3
- `NonCopyable`: Base class that deletes copy constructors
- `Parser`: Template meta parser generator
- `Range`: Pair of iterators
- `StringUtils`: Various string processing functions
