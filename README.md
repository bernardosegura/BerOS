# <img src="https://github.com/bernardosegura/BerOS/blob/master/img/BerOS.png" alt="BerOS" />
Es un Micro Sistema Operativo de 32 Bit, que ayuda a comprender como es el desarrollo de uno a un nivel muy básico, cuenta con un kernel simple el cual integra todo el funcionamiento del sistema.

# Creación del Sistema
> Es necesario contar con **gcc** y **as** para su compilación y creación.

## Linux y Windows 10  con WSL (Windows Subsystem for Linux )

Ingresa directamente al directorio src y ejecuta el make:
```bash
$ cd src
$ make build
```
# Creación de imagen ISO
> Utilizando la herramienta de **grub**
```bash
$ grub-mkrescue -o BerOS.iso ../build
```
> **grub-mkrescue** requiere de el paquete instalado **xorriso** para funcionar y para generar una imagen en 32 bit se requiere el paquete **grub-pc-bin** instalado.

# Ejecutar la Imagen
Se puede ejecutar la imagen grabando directamente en una USB mediante el comando **dd** "if=BerOS.iso of=/dev/sd+(**_letra USB_**)" o de manera virtual con alguna aplicación de virtualización, en este caso **qemu**:
> **Linux**
```bash
$ qemu-system-x86_64 -cdrom BerOS.iso
```
> **qemu-system-x86_64** requiere de el paquete instalado **qemu-system-x86** para funcionar.
#
> **Windows 10**
```cmd
>  C:\Program Files\qemu\qemu-system-x86_64 -cdrom BerOS.iso
```
> **qemu-system-x86_64.exe** requiere de el paquete instalado **qemu** para funcionar.

# Imagen ISO
Se preparó imagen precompilada.
- [BerOS.iso](https://drive.google.com/file/d/1jtpe4XTekoKPrGUVlu76IKjO-ZpMpben/view?usp=sharing)

# Resultado :)
El sistema es un **reloj** el cual muestra la fecha en la parte superior y un reloj pequeño el cual puede ser deshabilitado.
En la parte central está el reloj.
En la parte inferior muestra un panel con ayuda y las diferentes acciones que se pueden realizar.

### Fuente Normal
<img src="https://github.com/bernardosegura/BerOS/blob/master/img/scrNormal.png" alt="srcNormal" />

### Fuente Alien :alien:
<img src="https://github.com/bernardosegura/BerOS/blob/master/img/scrAlien.png" alt="srcAlien" />
