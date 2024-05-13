Rozwiązanie: Bartłomiej Galek

Aby uruchomić program, należy użyc make clean, a następnie:
make run-fifomaker ARGS="./consumer.x fifopipe consumer.txt ./producer.x fifopipe producer.txt"

Aby utworzyć potok nazwany z poziomu powłoki, należy użyć:
make create-pipe
Aby uruchomic programy producer.c i consumer.c z poziomu powłoki w oddzielnych terminalach, należy użyć:
make create-programs
Aby usunąć nazwany potok należy użyć
make delete-pipe