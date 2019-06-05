# TCP, UDP with nucleo

## requirement:

1. [STM32CubeMX](https://www.st.com/ja/development-tools/stm32cubemx.html)
2. [Truestudio](https://www.st.com/ja/development-tools/truestudio.html)
3. [Nucleo-H743ZI](https://www.st.com/ja/evaluation-tools/nucleo-h743zi.html)

## compile:

1. build in Truestudio
2. flash to the Nucleo-H743ZI

**note**: you can also change the GPIO configuration by STM32CubeMX

## usage:

3. create a new Ethernet connection with static IP (192.168.25.xxx, xxx: except 238) in host PC.

4. perform UDP receive test:

```
$ python3 Scripts/socket_udp_receive.py
```

5. perform TCP receive test:

```
$ python3 Scripts/socket_tcp_send.py
```

