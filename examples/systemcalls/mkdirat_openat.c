#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  const char *base_dir = ".";  // ベースとなるディレクトリ
  const char *new_dir = "example_dir";  // 作成するディレクトリ名
  const char *new_file = "example_file.txt";  // 作成するファイル名

  // ベースディレクトリをディレクトリFDとして開く
  int dir_fd = open(base_dir, O_RDONLY | O_DIRECTORY);
  if (dir_fd == -1) {
    perror("open base directory");
    return 1;
  }

  // mkdiratでディレクトリを作成
  if (mkdirat(dir_fd, new_dir, 0755) == -1) {
    perror("mkdirat");
    close(dir_fd);
    return 1;
  }
  printf("Directory '%s/%s' created successfully.\n", base_dir, new_dir);

  // 作成したディレクトリをディレクトリFDとして開く
  // int new_dir_fd = openat(dir_fd, new_dir, O_RDONLY | O_DIRECTORY);
  // if (new_dir_fd == -1) {
  //   perror("open new directory");
  //   close(dir_fd);
  //   return 1;
  // }

  // // openatでファイルを作成
  // int file_fd = openat(new_dir_fd, new_file, O_CREAT | O_WRONLY, 0644);
  // if (file_fd == -1) {
  //   perror("openat");
  //   close(new_dir_fd);
  //   close(dir_fd);
  //   return 1;
  // }

  // printf("File '%s/%s/%s' created successfully.\n", base_dir, new_dir, new_file);

  // // 後始末
  // close(file_fd);
  // close(new_dir_fd);
  // close(dir_fd);

  return 0;
}