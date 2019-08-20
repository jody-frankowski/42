## Considerations/Conventions

- `void **` as a generic pointer to pointer: Because it's easier even if unsafe.
  Even though `void **` shouldn't be used as a generic pointer
  (http://www.c-faq.com/ptrs/genericpp.html)
- We interface with `void *` as a generic pointer, but use `t_byte *` internally
  in order to do valid pointer arithmetic. It also helps us make less casts,
  which helps us have smaller lines, which is useful for the norminette.
- `void *` arithmetic: We sometimes use it because of the norminette.

## script/

 See [https://github.com/github/scripts-to-rule-them-all].

 script/kernel-doc stolen from the linux kernel [https://github.com/torvalds/linux/blob/master/scripts/kernel-doc] and adapted to fit the school's norm.
