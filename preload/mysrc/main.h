#define hoge(a) \
		hoge_d(a,__FUNCTION__)

void hoge_d(int a, const char *caller);

