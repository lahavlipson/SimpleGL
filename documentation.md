# SimpleGL Documentation

Here all the functions you can use with SimpleGL are documented with a brief description and a sample use case.

## Scene Class

### Constructing a Scene
```
Scene(char *vs = nullptr, char *fs = nullptr, const int width = 800, const int height = 600);
```

### Adding a mesh
```
Mesh_id add_mesh(
        std::variant<Shape, std::string> s, 
        const glm::vec3 color = {0.4, 0.4, 0.4}, 
        std::variant<std::unordered_map<std::string, int>, std::string> p = {});
```

### Adding a composite object