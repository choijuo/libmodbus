# libmodbus


c의 libmodbus 라이브러리를 활용하여 modbus TCP 통신을 하는 예제 소스입니다.


Master(Client) 와 Slave(Server) 로 나누어져 있으며

Slave 에서 TCP Server를 열어서 통신을 가능하게 하고 listen상태로 대기

modbus_mapping_new()를 통해 사용할 모드버스 레지스터의 메모리를 할당해줍니다.

여기서는 mapping->tab_register[0]~[4] 까지 5개의 값만 임시로 저장해놨습니다.

while(1) 무한루프 상태로 Master에서 요청이 올때마다 해당 recevie len과  reply len을 반환합니다.



Master에서는 modbus_read_registers(ctx,0,5,tab_reg) 를 통해서
address를 0부터 5개까지를 읽도록 했습니다.

slave에 요청하고 register[0]~[5] 까지만 출력하도록 설정해놨습니다.

*modbus_tcp에서는 slave id (unitID)를 설정할 필요가 없습니다.


sudo apt-get install -y libmodbus-dev

해당 소스 경로에서

 g++ -std=c++11 -I /usr/include/modbus TestSlave.c -o TestSlave -lmodbus -lpthread
 g++ -std=c++11 -I /usr/include/modbus TestMaster.c -o TestMaster -lmodbus -lpthread
 
 ./TestSlave 실행 후 ./TestMaster
