## Considerations/Conventions

- `void **` as a generic pointer to pointer: Because it's easier even if unsafe.
  Even though `void **` shouldn't be used as a generic pointer
  (http://www.c-faq.com/ptrs/genericpp.html)
- We interface with `void *` as a generic pointer, but use `t_byte *` internally
  in order to do valid pointer arithmetic. It also helps us make less casts,
  which helps us have smaller lines, which is useful for the norminette.
- `void *` arithmetic: We sometimes use it because of the norminette.
