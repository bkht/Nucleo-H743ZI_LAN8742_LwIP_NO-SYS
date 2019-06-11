# TCP, UDP with nucleo

## requirement:

1. [STM32CubeMX](https://www.st.com/ja/development-tools/stm32cubemx.html)
2. [Truestudio](https://www.st.com/ja/development-tools/truestudio.html)
3. [Nucleo-H743ZI](https://www.st.com/ja/evaluation-tools/nucleo-h743zi.html)

## compile:

1. build in Truestudio
2. flash to the Nucleo-H743ZI

### Generate from STM32CubeMX:
please check the MPU settings for ethernet DMA, based on following website:
- https://community.st.com/s/article/FAQ-Ethernet-not-working-on-STM32H7x3
- https://www.keshikan.net/gohantabeyo/?p=563
- http://nemuisan.blog.bai.ne.jp/?eid=215813
- https://www.st.com/content/ccc/resource/technical/document/application_note/group0/bc/2d/f7/bd/fb/3f/48/47/DM00272912/files/DM00272912.pdf/jcr:content/translations/en.DM00272912.pdf



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

