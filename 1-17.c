
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include <stdbool.h> 
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>
static bool is_file(const char* path) {
	struct stat path_stat;
    
	if (stat(path, &path_stat) != 0) {
		perror("stat failed");
		return false;
	}

	 return S_ISREG(path_stat.st_mode);
}

static void change_space( char* old, char* new) {
	while (*old) {
		if (*old == ' '){
            *old = '_';
		}
        *new = *old;
        new++;
		old++;
	}
}

static void rename_files_in_dir(const char* path) {
	DIR* p_dir = opendir(path);

	if (p_dir != NULL) {
		struct dirent* p_dirent;

		while ((p_dirent = readdir(p_dir)) != NULL) {
                if(readdir(p_dir) != NULL){
                    perror("no files in directory");
                }else {
			char old[PATH_MAX];
			sprintf(old, "%s/%s", path, p_dirent->d_name);

			if ((strcmp(p_dirent->d_name, ".") != 0) && (strcmp(p_dirent->d_name, "..") != 0) && is_file(old))
				{ char new_name[NAME_MAX + 1];
				    change_space(p_dirent->d_name, new_name);
					if (strlen(new_name) > 0)
						{ char new[PATH_MAX];
							sprintf(new, "%s/%s", path, new_name);
								if (rename(old, new) == 0)
									printf("renamed: %s -> %s\n", p_dirent->d_name, new_name);
                                else 
                                    perror("Failed to rename");
                        }
                    else 
                        printf("Cannot rename %s to <empty>\n", p_dirent->d_name);
                }
        }
        }
        if (closedir(p_dir) !=0){
        printf("Error with closedir");
        };
    }
}

int main(void){

rename_files_in_dir("./Test");

return 0;
}
