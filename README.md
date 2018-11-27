# w1-tempread
temperature reader for 1 wire temperature sensor 

## Wiring

**requires 4.7k ohms resistor for temperature sensor**

![Image](https://puu.sh/C8jMA/2cb11988e3.jpg)

## Install
In terminal

```bash
git clone https://github.com/Vrandus/w1-tempread.git
```

## Usage

initialize pin modes

```bash
./initMode.sh
```

prints raw temperature

```bash
./tempread
```

prints raw sensor data followed by raw temperature

```bash
./tempread -v
```

change default device ID

```bash
./tempread -d <id>
```
