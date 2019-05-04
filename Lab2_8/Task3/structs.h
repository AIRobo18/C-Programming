struct inv_table_page {
	int pid;
	int page;
	int time_created;
};

struct inv_table {
	int frame_size;
	int mem_size;
	int number_of_pages; // equal to (mem_size / frame_size)
	struct inv_table_page *pages;
};