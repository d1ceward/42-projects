# 42-libft
The libft is a C languague library (like libc with less & more functions) for everyday use at school 42.
## Convert functions
```C
int		ft_abs(int n);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
int		ft_tolower(int c);
int		ft_toupper(int c);
```
## Lists functions
```C
void	ft_lstadd(t_list **alst, t_list *new);
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void	ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list	*ft_lstnew(void const *content, size_t content_size);
void	ft_lstpushback(t_list **blst, void const *content, size_t content_size);
```
## Math functions
```C
int	ft_sqrt(int n);
int	ft_max(int i, int j);
int	ft_min(int i, int j);
```
## Memory functions
```C
void	ft_bzero(void *s, size_t n);
void	*ft_memalloc(size_t size);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_memdel(void **ap);
void	*ft_memmove(void *s1, const void *s2, size_t n);
void	*ft_memset(void *s, int c, size_t n);
```
## Print functions
```C
void	ft_exit(const char *str, int status);
int		ft_putchar(char c);
int		ft_putchar_fd(char c, int fd);
int		ft_putendl(char const *s);
int		ft_putendl_fd(char const *s, int fd);
int		ft_putnbr(int n);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr(char const *s);
int		ft_putstr_fd(char const *s, int fd);
int		ft_putnstr(char const *s, size_t len);
int		ft_putnstr_fd(char const *s, size_t len, int fd);
void	ft_putwchar(wchar_t wc);
void	ft_putwchar_fd(wchar_t wc, int fd);
void	ft_putwstr(wchar_t const *wstr);
void	ft_putwstr_fd(wchar_t const *wstr, int fd);
void	ft_putnwstr(const wchar_t *wstr, size_t len);
void	ft_putnwstr_fd(const wchar_t *wstr, size_t len, int fd);
void	ft_putnbrbase(uintmax_t n, char *base);
void	ft_putnbrbase_fd(uintmax_t n, char *base, int fd);
```
## Strings functions
```C
char	*ft_stradd(char *s1, char *s2);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
void	ft_strclr(char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *s1, const char *s2);
void	ft_strdel(char **as);
char	*ft_strdup(const char *s);
int		ft_strequ(char const *s1, char const *s2);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strncat(char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *s1, const char *s2, size_t n);
char	*ft_strndup(const char *s1, size_t n);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strnew(size_t size);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	**ft_strsplit(char const *s, char c);
char	*ft_strstr(const char *s1, const char *s2);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s);
size_t	ft_strnlen(const char *s, size_t maxlen);
size_t	ft_wstrlen(wchar_t *wstr);
```
## Utility functions
```C
int	ft_digit_count(int n);
int	ft_isalnum(int c);
int	ft_isalpha(int c);
int	ft_isascii(int c);
int	ft_isdigit(int c);
int	ft_isprint(int c);
int	ft_isspace(int c);
int	get_next_line(int const fd, char **line); 
```
