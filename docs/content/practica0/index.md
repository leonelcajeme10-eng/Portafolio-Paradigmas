+++
date = '2026-02-20T20:38:12-08:00'
draft = false
title = 'Practica 0: Manejo de Repositorios (Markdown, Git, Hugo)'
+++

<div align="center">

# Paradigmas de la Programacion: Practica 0
## Markdown · Git · GitHub · Hugo · GitHub Actions

---

**Materia:** Paradigmas de la Programacion  
**Nombre:** _Leonel Cajeme Garcia_  
**Matricula:** _379154_  
**Grupo:** _Ing. Software 941_  
**Profesor:** _Jose Carlos Gallegos Mariscal_  
**Fecha:** _20 de febrero de 2026_

---

> 📁 Repositorio en GitHub: [github.com/tu-usuario/tu-repositorio](https://github.com/tu-usuario/tu-repositorio)  
> 🌐 Página estática (GitHub Pages): [tu-usuario.github.io/tu-repositorio](https://tu-usuario.github.io/tu-repositorio)

</div>

<!--more-->

---

## Descripción de la Práctica

Esta práctica tiene como objetivo familiarizarse con las herramientas fundamentales del desarrollo de software moderno. A lo largo de tres sesiones se trabajó con **Markdown** para redactar documentación con formato, **Git y GitHub** para el control de versiones y trabajo colaborativo, y finalmente **Hugo junto con GitHub Actions** para generar y publicar de forma automatizada un sitio web estático.

Estas herramientas son ampliamente utilizadas en la industria del software, tanto en proyectos personales como en equipos de desarrollo profesional. Dominarlas desde etapas tempranas representa una ventaja significativa para cualquier ingeniero de software.

> **Nota:** Aunque se trabajó en Windows, se utilizó **Git Bash** para ejecutar comandos de Linux, ya que en entornos profesionales y en la nube (AWS, GCP, Azure) el sistema operativo predominante es Linux o Unix.

---

## Desarrollo de la Práctica

### Sesión 1 – Markdown

#### ¿Qué es Markdown?

**Markdown** es un lenguaje de marcado ligero creado en 2004 por **John Gruber** con la colaboración de Aaron Swartz. Su propósito es permitir escribir texto con formato de una manera sencilla y legible en texto plano, que luego puede convertirse fácilmente a HTML u otros formatos.

A diferencia de HTML, Markdown es legible incluso sin ser procesado, lo que lo hace ideal para documentación técnica, archivos `README`, blogs y notas.

#### ¿Para qué se utiliza?

Markdown se usa ampliamente en:

- **GitHub / GitLab**: archivos `README.md`, wikis y comentarios en issues/pull requests.
- **Blogs y sitios estáticos**: plataformas como Hugo, Jekyll o Ghost usan Markdown para el contenido.
- **Documentación técnica**: proyectos de software que documentan su API o guías de uso.
- **Herramientas de notas**: Notion, Obsidian, VS Code y otros editores lo soportan nativamente.
- **Correos y mensajería**: Slack, Discord y Teams soportan subconjuntos de Markdown.

#### Sintaxis practicada

**Encabezados**
````markdown
# Encabezado H1
## Encabezado H2
### Encabezado H3
````

**Énfasis de texto**
````markdown
**Texto en negrita**
*Texto en cursiva*
~~Texto tachado~~
`código en línea`
````

**Listas**
````markdown
- Elemento sin orden
  - Sub-elemento

1. Primer elemento
2. Segundo elemento
````

**Vínculos e imágenes**
````markdown
[Texto del enlace](https://www.ejemplo.com)
![Texto alternativo](ruta/imagen.png)
````

**Bloques de código**
````markdown
```python
def hola_mundo():
    print("Hola, Mundo!")
```
````

**Tablas**
````markdown
| Columna 1 | Columna 2 | Columna 3 |
|-----------|-----------|-----------|
| Dato 1    | Dato 2    | Dato 3    |
````

**Citas y checkboxes**
````markdown
> Esto es una cita.

- [x] Tarea completada
- [ ] Tarea pendiente
````

---

### Sesión 2 – Git y GitHub

#### ¿Qué es Git?

**Git** es un sistema de **control de versiones distribuido** creado por **Linus Torvalds** en 2005 para gestionar el desarrollo del kernel de Linux. Permite rastrear cambios en archivos a lo largo del tiempo, trabajar en paralelo con múltiples desarrolladores y revertir cambios cuando sea necesario.

Sus principales características son:

- **Distribuido**: cada desarrollador tiene una copia completa del historial del repositorio.
- **Velocidad**: operaciones locales sin necesidad de conexión constante a un servidor.
- **Ramificación (branching)**: permite crear ramas de trabajo independientes y fusionarlas.
- **Integridad**: usa hashes SHA-1 para garantizar la integridad de los datos.

#### ¿Qué es GitHub?

**GitHub** es una plataforma de alojamiento en la nube para repositorios Git, adquirida por Microsoft en 2018. Ofrece herramientas de colaboración como Pull Requests, Issues, GitHub Actions, GitHub Pages, Wikis y gestión de proyectos.

#### Comandos esenciales utilizados
````bash
# Configuración inicial
git config --global user.name "Tu Nombre"
git config --global user.email "tucorreo@ejemplo.com"
git config --list

# Inicializar y clonar
git init
git clone https://github.com/usuario/repositorio.git

# Ciclo básico de trabajo
git status
git add .
git commit -m "Descripción del cambio"
git log --oneline

# Ramas
git branch
git checkout -b nueva-rama
git merge nombre-rama

# Repositorio remoto
git remote add origin https://github.com/usuario/repo.git
git push origin main
git pull origin main
````

#### Crear y subir un repositorio a GitHub

1. Crear el repositorio en [github.com](https://github.com) con nombre, descripción y visibilidad.
2. Inicializar localmente y conectar con el remoto:
````bash
git init
git add .
git commit -m "Primer commit: inicio del proyecto"
git remote add origin https://github.com/tu-usuario/tu-repositorio.git
git branch -M main
git push -u origin main
````

3. Configurar llave SSH para evitar ingresar credenciales en cada push:
````bash
ssh-keygen -t ed25519 -C "tucorreo@ejemplo.com"
cat ~/.ssh/id_ed25519.pub
# Agregar la llave en GitHub: Settings → SSH and GPG Keys → New SSH key
````

---

### Sesión 3 – Hugo y GitHub Actions

#### ¿Qué es Hugo?

**Hugo** es un generador de sitios estáticos de código abierto escrito en **Go**, reconocido por ser uno de los más rápidos del mercado. Convierte archivos Markdown y plantillas en un sitio web estático listo para publicar, sin necesidad de base de datos ni servidor backend.

Sus ventajas principales son su velocidad extrema, portabilidad, soporte nativo de Markdown y una amplia biblioteca de temas gratuitos en [themes.gohugo.io](https://themes.gohugo.io).

#### ¿Qué es GitHub Actions?

**GitHub Actions** es la plataforma de **CI/CD** de GitHub. Permite automatizar flujos de trabajo directamente desde el repositorio mediante archivos YAML en `.github/workflows/`. En esta práctica se usó para compilar el sitio Hugo y desplegarlo en GitHub Pages con cada `push` a `main`.

#### Creación del sitio
````bash
# Instalar Hugo (Windows con Chocolatey)
choco install hugo-extended

# Crear el sitio
hugo new site mi-portafolio
cd mi-portafolio
git init

# Agregar tema Ananke
git submodule add https://github.com/theNewDynamic/gohugo-theme-ananke.git themes/ananke
echo 'theme = "ananke"' >> hugo.toml

# Crear primer post
hugo new posts/practica0.md

# Vista previa local
hugo server -D
# Acceder en: http://localhost:1313

# Generar sitio estático
hugo
````

#### Configuración de GitHub Actions

Se creó el archivo `.github/workflows/hugo.yml` con el siguiente workflow:
````yaml
name: Deploy Hugo site to GitHub Pages

on:
  push:
    branches:
      - main
  workflow_dispatch:

permissions:
  contents: read
  pages: write
  id-token: write

jobs:
  build:
    runs-on: ubuntu-latest
    env:
      HUGO_VERSION: 0.128.0
    steps:
      - name: Install Hugo CLI
        run: |
          wget -O ${{ runner.temp }}/hugo.deb \
          https://github.com/gohugoio/hugo/releases/download/v${HUGO_VERSION}/hugo_extended_${HUGO_VERSION}_linux-amd64.deb \
          && sudo dpkg -i ${{ runner.temp }}/hugo.deb
      - name: Checkout repository
        uses: actions/checkout@v4
        with:
          submodules: recursive
      - name: Setup Pages
        id: pages
        uses: actions/configure-pages@v5
      - name: Build with Hugo
        run: hugo --gc --minify --baseURL "${{ steps.pages.outputs.base_url }}/"
      - name: Upload artifact
        uses: actions/upload-pages-artifact@v3
        with:
          path: ./public

  deploy:
    runs-on: ubuntu-latest
    needs: build
    steps:
      - name: Deploy to GitHub Pages
        id: deployment
        uses: actions/deploy-pages@v4
````

Tras hacer `git push`, GitHub Actions compiló y publicó el sitio automáticamente en `https://tu-usuario.github.io/mi-portafolio/`.

---

## Conclusiones

A lo largo de estas tres sesiones se adquirieron habilidades fundamentales para cualquier desarrollador de software moderno:

- **Markdown** permite documentar proyectos de manera profesional usando solo texto plano, con una curva de aprendizaje mínima y compatibilidad universal en plataformas como GitHub, Notion y VS Code.
- **Git** proporciona control total sobre el historial de un proyecto, permitiendo experimentar sin miedo a perder trabajo y colaborar eficientemente en equipo gracias a su sistema de ramas.
- **GitHub** extiende las capacidades de Git con herramientas de colaboración, visibilidad pública del trabajo y servicios adicionales como Pages y Actions que facilitan el ciclo completo de desarrollo.
- **Hugo** demuestra que es posible tener un sitio web rápido, seguro y fácil de mantener sin necesidad de frameworks complejos ni bases de datos, usando únicamente Markdown como fuente de contenido.
- **GitHub Actions** cierra el ciclo automatizando el despliegue: con un simple `git push`, el sitio se compila y publica automáticamente sin intervención manual.

La combinación de estas herramientas forma la base de un **portafolio profesional** versionado, publicado y mantenido de manera eficiente, y representa el punto de partida ideal para el desarrollo de software moderno.

---