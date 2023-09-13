FROM ubuntu:23.10
RUN apt-get update -y
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y check
RUN apt-get install -y make
RUN apt-get install -y valgrind
RUN apt-get install -y g++
RUN apt-get install -y lcov
RUN apt-get install -y html2text
RUN apt-get install -y links
RUN apt-get install -y clang-format
RUN apt-get install -y libsubunit-dev

ADD . /project
WORKDIR /project

# Дюжина инструкций Dockerfile

#volumes

# docker build -t ubuntu_23_10 .

# docker run -it -v C:\C6_s21_matrix-1\src:/mounted  ubuntu_23_10 /bin/bash        -my mackbook

#в корне Линукса можно выйти через cd .. ищешь папку mounted она будет той самой общей папкой для линукса и мака


# FROM — задаёт базовый (родительский) образ.
# LABEL — описывает метаданные. Например — сведения о том, кто создал и поддерживает образ.
# ENV — устанавливает постоянные переменные среды.
# RUN — выполняет команду и создаёт слой образа. Используется для установки в контейнер пакетов.
# COPY — копирует в контейнер файлы и папки.
# ADD — копирует файлы и папки в контейнер, может распаковывать локальные .tar-файлы.
# CMD — описывает команду с аргументами, которую нужно выполнить когда контейнер будет запущен. Аргументы могут быть переопределены при запуске контейнера. В файле может присутствовать лишь одна инструкция CMD.
# WORKDIR — задаёт рабочую директорию для следующей инструкции.
# ARG — задаёт переменные для передачи Docker во время сборки образа.
# ENTRYPOINT — предоставляет команду с аргументами для вызова во время выполнения контейнера. Аргументы не переопределяются.
# EXPOSE — указывает на необходимость открыть порт.
# VOLUME — создаёт точку монтирования для работы с постоянным хранилищем.