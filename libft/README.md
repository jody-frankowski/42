# `libft` - A Custom Libc and More

Subject: [libft.en.pdf](libft.en.pdf)

This repository represents the current version of my `libft`. It does not
represent the one given for the correction anymore. Your best bet would be to
look at this commit: 8191682fe79b12b3ae583c7671c524be453eda96.

It uses both [libtest](../libtest) and [libunit](../libunit) for the tests,
`libtest` being the old legacy one, and `libunit` the new one, used when
possible now.

## Considerations/Conventions

- `void **` is used as a generic pointer to pointer: Because it's easier even if
  unsafe. Even though `void **` shouldn't be used as a generic pointer
  (http://www.c-faq.com/ptrs/genericpp.html)
- We interface with `void *` as a generic pointer, but use `t_byte *` internally
  in order to do valid pointer arithmetic. It also helps us make less casts,
  which helps us have smaller lines, which is useful for The Norm.
- `void *` arithmetic: We sometimes use it because it helps with The Norm.

## script/

 See [https://github.com/github/scripts-to-rule-them-all].

 script/kernel-doc stolen from the linux kernel
 [https://github.com/torvalds/linux/blob/master/scripts/kernel-doc] and adapted
 to fit the school's Norm.
