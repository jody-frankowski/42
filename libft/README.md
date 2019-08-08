## Considerations

- `void *` arithmetic: We use it because of norminette
- `void **` as a generic pointer to pointer: Because "sanity"
// void ** cannot be used as a generic pointer (http://www.c-faq.com/ptrs/genericpp.html)

// What seems to be best (imho) is to interface with void* but use t_byte
// internally
