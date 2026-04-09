#include <ctype.h>
#include <math.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "genomikon.h"

static void yikes(const char *msg) {
	fprintf(stderr, "geney ERROR: %s\n", msg);
	exit(1);
}

int VERBOSE = 0;
int DEBUG = 0;

static char *usage = "\
geney - connect to SQLite database and create genes\n\n\
usage: geney <sqlite.db>\n\
options:\n\
  --verbose          report stuff\n\
  --debug            report more stuff\n\
";

int main (int argc, char ** argv) {

	// CLI - setup
	gkn_set_program_name(argv[0]);
	gkn_register_option("--verbose", 0);
	gkn_register_option("--debug", 0);
	gkn_parse_options(&argc, argv);
	if (argc == 1) gkn_exit("%s", usage);

	// CLI - harvest
	if (gkn_option("--verbose")) VERBOSE = 1;
	if (gkn_option("--debug")) DEBUG = 1;

	char *dbname = argv[1];
	if (access(dbname, F_OK) != 0) yikes("no such database file");

	// SQLite
	sqlite3 *db;
	int rc = sqlite3_open(dbname, &db);
	if (rc != SQLITE_OK) yikes(sqlite3_errmsg(db));
	const char *sql = "SELECT uid, beg, end FROM feature WHERE type = 'gene';";
	sqlite3_stmt *stmt;
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) yikes(sqlite3_errmsg(db));    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
    	const unsigned char *name = sqlite3_column_text(stmt, 0);
    	int beg = sqlite3_column_int(stmt, 1);
    	int end = sqlite3_column_int(stmt, 2);
    	printf("%s %d %d %d\n", name, beg, end, end - beg + 1);
    }
	sqlite3_finalize(stmt);
    sqlite3_close(db);


	if (VERBOSE && DEBUG) yikes("end");

	return 0;
}

