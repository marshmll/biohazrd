<a id="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/marshmll/biohazrd">
    <img src="https://raw.githubusercontent.com/marshmll/biohazrd/main/images/logo.png" alt="Logo" width="150" height="auto">
  </a>

  <h3 align="center">2D Game Engine - Codename "BIOHAZRD"</h3>

  <p align="center">
    A 2D Game Engine built with C++ and Simple And Fast Multimedia Library (SFML)
    <br />
    <a href="https://github.com/marshmll/biohazrd"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/marshmll/biohazrd">View Demo</a>
    •
    <a href="https://github.com/marshmll/biohazrd/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#configurating-and-running">Configurating and running</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#running-the-oroject">Running the project</a></li>
      </ul>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![BIOHAZRD][cover]](https://github.com/marshmll/biohazrd)

The BIOHAZRD 2D Game Engine is a project that initially had the intent of creating a two-dimentional game that runs on it's own engine. As the project grew, features as GUI standards, animations, hitbox, collision, tilemap, entities, skills, shaders and more were implemented and designed to be easily used and replicated.

The name "BioHazrd" is a homage to a game designed in march 2024, originally built in the Construct 3 Web Game Engine in the first period of my Bachelor in Computer Science at Pontifical Catholic University of Paraná. The game was inspired in Capcom's "BioHazard" (the well-known Resident Evil), with 2D graphics and a simple lore, but with an amazing creativity.

This initial spark provoked the start of this project. And now, with over 10,000 lines of code, there are some solid infrastructure already done, but the project is far away from being finished.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

This project was built with:

* [![C++][C++]][C++-url]
* [![SFML][SFML]][SFML-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Configurating and running

This project has shell scripts to help building the project. **It is recommended to use a Debian-based distro** to run this project, although it is possible to build and use in Windows.

This manual covers only Debian-based GNU/Linux distros.

### Prerequisites

Install these dependencies in your machine.
* Git
  ```sh
  sudo apt-get install git
  ```
* CMake
  ```sh
  sudo apt-get install cmake
  ```
* G++
  ```sh
  sudo apt-get install g++
  ```
* Note
  ***It's recommended to have atleast OpenGL 2.0 available.***

### Running the project

1. Install all needed dependencies by running the ```./install-dependencies.sh``` script.
2. Run ```./debug.sh``` or the ```./release.sh``` script, if you want either the Debug or the Release mode build.
3. Wait for the SFML lib to build. It may take a while, but just at the first build.
4. When the code is built, the shell script will automatically run the executable.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Top contributors:

<a href="https://github.com/marshmll/biohazrd/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=marshmll/biohazrd" alt="contrib.rocks image" />
</a>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Renan Andrade - [Instagram](https://instagram.com/renan._.and) - renandasilvaoliveiraandrade@gmail.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. I've included a few of my favorites to kick things off!

* [Pedro Senes](https://github.com/prussianmaster1871)
* [Victor Fadel](https://github.com/VictorFadel06)
* [OpenGameArt](https://opengameart.org/)
* [SFML](https://www.sfml-dev.org/)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/marshmll/biohazrd.svg?style=for-the-badge
[contributors-url]: https://github.com/marshmll/biohazrd/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/marshmll/biohazrd.svg?style=for-the-badge
[forks-url]: https://github.com/marshmll/biohazrd/network/members
[stars-shield]: https://img.shields.io/github/stars/marshmll/biohazrd.svg?style=for-the-badge
[stars-url]: https://github.com/marshmll/biohazrd/stargazers
[issues-shield]: https://img.shields.io/github/issues/marshmll/biohazrd.svg?style=for-the-badge
[issues-url]: https://github.com/marshmll/biohazrd/issues
[license-shield]: https://img.shields.io/github/license/marshmll/biohazrd.svg?style=for-the-badge
[license-url]: https://github.com/marshmll/biohazrd/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/renan-oliveira-andrade
[cover]: https://raw.githubusercontent.com/marshmll/biohazrd/main/images/screenshot.png
[C++]: https://img.shields.io/badge/-C++-333333?style=flat&logo=C%2B%2B
[C++-url]: https://en.cppreference.com/w/
[SFML]: https://img.shields.io/badge/-SFML-333333?style=flat&logo=sfml
[SFML-url]: https://www.sfml-dev.org/