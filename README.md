# molecular-util
Collection of utility classes used by other molecular components

## Classes

### Math

- `AxisAlignedBox`
- `Math`
- `Matrix`: Matrix template
- `Matrix3`
- `Matrix4`
- `Quaternion`
- `SphericalHarmonics`
- `Vector`: Vector template
- `Vector3`
- `Vector4`

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
- `ReadStream`
- `StreamStorage`
- `TextStream`

### 3D Data Handling

- `BufferInfo`: Information about vertex attribute data in a GPU buffer
- `CharacterAnimation`: Skeletal animation with custom file format
- `FloatToHalf`: Create 16-bit floats
- `GlConstants`
- `Mesh`
- `MeshUtils`
- `PixelFormat`

### Various

- `Blob`: Holds binary data. Contents are not initialized. Movable, non-copyable.
- `CommandLineParser`: Easy processing of argc and argv
- `Hash`: Compile-time MurmurHash3
- `NonCopyable`: Base class that deletes copy constructors
- `Parser`: Template meta parser generator
- `Range`: Pair of iterators
- `StringUtils`
