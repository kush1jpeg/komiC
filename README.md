<table>
<tr>
<td>

<img src="assets/komi.gif" width="400"/>

</td>
<td>

# komiC 🌸  
*A compiler for **komiLang**, written from scratch in C.*  

komiLang is a small, readable language with syntax drawn from C, Python,
and a touch of Go. komiC is my attempt to build every stage of a
traditional compiler by hand, with no parser generators or compiler
frameworks.


> **Work in progress.**

</td>
</tr>
</table>


### hitherto-

The current repo is in the early frontend stage and will definitely be following the traditional pipeline of compiler construction.

source → lexer → tokens → Pratt expression parser → AST → future semantic analysis → IR → backend


- mmap-backed source file loading
- tokenization
- Pratt-style expression parsing
- AST construction
- parser diagnostics scaffolding
- architecture laid out for the next compiler stages

### docs-

- [Language design notes](docs/language.md) (work in progress)
- [Token definitions](docs/token.md)


### example-

```komi
let x: int = 10;

while x < 20 {
    x = x + 1;
}
```


### Requirements

- A C compiler [>=C11]
- `gcc` (used for preprocessing and linking)
- GNU `as` (assembler)
- Linux x86-64

#### 📚 License

This project is licensed under the **MIT License**.  
See [LICENSE](./LICENSE) file for full details.

---

#### 👤 Author: kush1jpeg

> "we finally understand komi's language ! "
