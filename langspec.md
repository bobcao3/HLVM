# HLVM Language Specification

## Basic Law

As this project is called HLVM, the language hereby specifies is called HL.

HL is a staticly typed, non OOP high level language that can be interpreted, JIT, or compiled into binaries.

HL has some C-like syntax, with the ambiguity (C is usually ambigious for newbee programmers) removed.

## Basic Objects / Types

Primitive Type:

- Pass by copy
- Static size, usually small
- Can not be inherited by new types
- Integers:
  - Signed:
    - `i8`
    - `i16`
    - `i32`
    - `i64`
  - Unsigned
    - `u8`
    - `u16`
    - `u32`
    - `u64`
- Floating point:
  - `f32`
  - `f64`
- Limited Size Vector
  - 2d vector
    - `i8vec2`
    - `i16vec2`
    - `i32vec2`
    - `i64vec2`
    - `u8vec2`
    - `u16vec2`
    - `u32vec2`
    - `u64vec2`
    - `f32vec2`
    - `f64vec2`
  - 3d vector
    - Similar to 2d, just `[type]vec3`
  - 4d vector
    - Similar to 2d, just `[type]vec4`
  - 2d matrices (2x2)
    - Similar to 2d vector, just `[type]mat2`
  - 3d matrices (3x3)
    - Similar to 2d vector, just `[type]mat3`
  - 4d matrices (4x4)
    - Similar to 2d vector, just `[type]mat4`

Structs:

- Pass by reference
- Reference counting for memory management
- Can be inherited to create sub-structs
- Can be anonymous

Functions

- Essentially executable data
- Can be inherited
- Can be overloaded
- Can be anonymous (lambda?)

## Sample snippet

```
{u32, array} tokenize(var s : string) {
    /* Variable decleration */
    var out : array(string), count : u32
    /* Constants decleration, with bracket initializers */
    const whitespace : array(string){".", " ", "\t", "\n"}
    /* Array concatnation, implemented internally through operator overloading */
    const delim : whitespace + array(string){";", ":", "{", "}"}

    for (var t : split(s, delim)) {
        /* if statements must be followed by code block: {} */
        if (!is_empty(t) && !in(t, whitespace)) {
            append(out, t)
        }
        count ++
    }

    /* Returns an anonymous struct, type is inferenced */
    /* When this function is compiled and mapped to a C function, this essentially returns a pointer */
    return {count, out}
}
```

## Is this a joke?

Probably. I don't know.
