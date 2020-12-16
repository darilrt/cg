# CG-Docs

## Index
- [math](#cg::math)
- time
- input
- display
- shader
- debug
- key_code
- Component
- GameObject
- Scene
- core
    - Window
    - Camera2D
    - Shader
    - Material
    - MeshRenderer
    - Socket

### components

- Sprite

# cg::math
## index
- Data types
- [Vec2](#cg::math::Vec2)
- [Vec3](#cg::math::Vec3)
- [Vec4](#cg::math::Vec4)
- Ray

# cg::math::Vec2

constructors:
- Vec2\<T\>()
- Vec2\<T\>(T x)
- Vec2\<T\>(T x, T y)

propertypes:
- T x
- T y

methods:
- dot(const Vec2\<T\> &v) -> T
- unlit(void)
- unlit(void) -> 
- length(void) -> T
- rot(T degrees) -> Vec2\<T\> 
- corss(const Vec2\<T\> &v) -> T
- xy(void) -> Vec2\<T\>
- yx(void) -> Vec2\<T\>
- to_string(void) -> std::string

operators for +, -, *, /, =, +=, -=, ==

# cg::math::Vec3

constructors:
- Vec3\<T\>()
- Vec3\<T\>(T x)
- Vec3\<T\>(T x, T y)
- Vec3\<T\>(T x, T y, T z)

propertypes:
- T x
- T y
- T z

methods:
- dot(const Vec3\<T\> &v) -> T
- unlit(void)
- unlit(void) -> 
- length(void) -> T
- rot(T degrees) -> Vec3\<T\> 
- corss(const Vec3\<T\> &v) -> T
- xy(void) -> Vec3\<T\>
- yx(void) -> Vec3\<T\>
- to_string(void) -> std::string

operators for +, -, *, /, =, +=, -=, ==, *=, /=

# cg::math::Vec4

constructors:
- Vec4\<T\>()
- Vec4\<T\>(T x)
- Vec4\<T\>(T x, T y)
- Vec4\<T\>(T x, T y, T z)
- Vec4\<T\>(T x, T y, T z, T w)

propertypes:
- T x
- T y
- T z
- T w

methods:
- dot(const Vec4\<T\> &v) -> T
- unlit(void)
- unlit(void) -> 
- length(void) -> T
- rot(T degrees) -> Vec4\<T\> 
- corss(const Vec4\<T\> &v) -> T
- xy(void) -> Vec4\<T\>
- yx(void) -> Vec4\<T\>
- to_string(void) -> std::string

operators for +, -, *, /, =, ==