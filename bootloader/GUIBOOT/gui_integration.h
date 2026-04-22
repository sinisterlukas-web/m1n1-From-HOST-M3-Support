# GUI Integration Layer for m1n1

This header file defines the C++ GUI interface for the m1n1 bootloader.

## Class: GUIM1n1

### Methods:
- `void initialize();`
- `void renderFrame();`
- `void shutdown();`

```cpp
class GUIM1n1 {
public:
    void initialize();
    void renderFrame();
    void shutdown();
};
```