#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024 // 파일에서 한 번에 읽을 버퍼 크기

uint32_t read_file(char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file: %s %s\n", filename, strerror(errno)); //strerror(errno): error display
        exit(1);
    }

    uint32_t number;
    if (fread(&number, sizeof(uint32_t), 1, file) != 1) { //sizeof(number) instead of '1'
        printf("Failed to read file: %s\n", filename);
        exit(1);
    }

    fclose(file);
    return ntohl(number);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    uint32_t numbers[2]; // 파일에서 읽은 두 숫자를 저장할 배열

    for (int i = 1; i < argc; ++i) {
        numbers[i - 1] = read_file(argv[i]);
    }

    printf("%u (0x%x) + %u (0x%x) = %u (0x%x)\n", numbers[0], numbers[0], numbers[1], numbers[1], numbers[0] + numbers[1], numbers[0] + numbers[1]);

    return 0;
}
