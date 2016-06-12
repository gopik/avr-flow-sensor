void set_cursor(int pos);
void write_string(const char* const str);


// 16x2 character display commands
void clear_display(char* rs, char* rw, char db) {
	*rs = 0;
	*rw = 0;
	db = 0x01;
}
