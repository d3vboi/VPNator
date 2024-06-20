#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

void print_usage() {
    printf("Usage: vpnator -c <country>\n");
    printf("       vpnator --country <country>\n");
    printf("       <country> should be 'nl', 'us', or 'jp'.\n");
}

int directory_exists(const char* directory) {
    struct stat info;
    if (stat(directory, &info) != 0) {
        return 0; // Directory does not exist
    }
    return (info.st_mode & S_IFDIR) != 0;
}

char* get_random_ovpn_file(const char* directory) {
    struct dirent* entry;
    DIR* dp = opendir(directory);
    if (dp == NULL) {
        perror("opendir");
        return NULL;
    }

    char* ovpn_files[256];
    int file_count = 0;

    while ((entry = readdir(dp))) {
        if (strstr(entry->d_name, ".ovpn")) {
            ovpn_files[file_count] = strdup(entry->d_name);
            file_count++;
        }
    }
    closedir(dp);

    if (file_count == 0) {
        fprintf(stderr, "No .ovpn files found in directory %s\n", directory);
        return NULL;
    }

    srand(time(NULL));
    int random_index = rand() % file_count;

    char* selected_file = malloc(strlen(directory) + strlen(ovpn_files[random_index]) + 2);
    sprintf(selected_file, "%s/%s", directory, ovpn_files[random_index]);

    for (int i = 0; i < file_count; i++) {
        free(ovpn_files[i]);
    }

    return selected_file;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        print_usage();
        return 1;
    }

    char* country = NULL;

    if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--country") == 0) {
        country = argv[2];
    } else {
        print_usage();
        return 1;
    }

    char directory[100]; // Increase size to accommodate longer paths

    if (strcmp(country, "nl") == 0 || strcmp(country, "us") == 0 || strcmp(country, "jp") == 0) {
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "Error: HOME environment variable is not set.\n");
            return 1;
        }
        snprintf(directory, sizeof(directory), "%s/.config/vpnator/%s", home, country);
    } else {
        print_usage();
        return 1;
    }

    if (!directory_exists(directory)) {
        fprintf(stderr, "Error: Directory %s does not exist.\n", directory);
        return 1;
    }

    char* ovpn_file = get_random_ovpn_file(directory);
    if (ovpn_file == NULL) {
        return 1;
    }

    char command[512];
    snprintf(command, sizeof(command), "sudo openvpn --config %s", ovpn_file);

    printf("Connecting to VPN using configuration file: %s\n", ovpn_file);
    int result = system(command);

    free(ovpn_file);

    return result;
}
