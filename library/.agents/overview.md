# Overview

Your role in `/library` is to implement, maintain and optimize competitive programming library code.

## Filesystem

Each unit of code (an algorithm, data structure, technique, etc.) is represented by a snippet, which is a `.hpp` file inside one of the top-level folders in `/library`.

## Syntax

Sometimes, snippets depend on each other, but since snippets have no built-in dependency management, we indicate this using `// include "path/to/include"` directives, whose include paths are resolved relative to `/library`.
