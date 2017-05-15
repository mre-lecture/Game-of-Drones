# Game of Drones - _Mixed reality is coming._
Ziel des Projekts ist es, die visuelle Wahrnehmung von Maschinen in einer augmentierten Realität zu visualisieren und wird im Rahmen der Kurse "Robotik" und "Mixed Reality" der Hochschule Mannheim (HS-MA) durchgeführt. Es hebt sich durch seinen technischen Anspruch und ambitionierte Ziele hervor.

## Beteiligt
*   Projektdurchführung
    * Marie-Darline Mroß _(ROB/MRE)_
    * Moritz Thomas _(ROB/MRE)_
    * Sebastian Schuler _(MRE)_
*   Betreuung
    * Prof. Thomas Ihme _(ROB)_
    * Marc Durstewitz _(MRE, empea AR VR GmbH)_
    * Prof. Thomas Smits _(MRE)_

## Einleitung

### Motivation
Mit steigender Nutzung des Buzzwords "Industrie 4.0" gewinnt auch die Entwicklung und Gestaltung der Mensch-Maschine-Kollaboration zunehmend an Bedeutung. Dies beinhaltet eine Reihe von Herausforderungen, die unter Anderem von der Informatik behandelt werden. Viele dieser Herausforderungen sind jedoch sehr komplex und bedürfen der Schaffung einer gemeinsamen Kommunikationsbasis aller beteiligten Akteure, was wiederum eine gemeinsame Wahrnehmung und Interpretation derselbigen voraussetzt. Mithilfe aktuellster Hardware betrachten wir die visuelle Wahrnehmungen von Maschinen und führen diese mit der beliebiger Anwender zusammen, um schließlich eine Möglichkeit zur Interaktion zwischen beiden zu implementieren.

### Verbundprojekt ROB/MRE
Der Kurs "Mixed Reality" wurde in Zusammenarbeit mit der empea AR VR GmbH erstmals im Sommersemester 2017 an der Hochschule angeboten, von Herrn Marc Durstewitz und Herrn Prof. Thomas Smits geleitet und behandelt aktuelle Technologien in den Bereichen Augmented und Virtual Reality, unter Anderem Microsofts Datenbrille "HoloLens".
Im Rahmen des von Herrn Prof. Thomas Ihme betreuten Kurs "Robotik" entstand die Idee, einen Roboter zu entwickeln. **[TODO]**

## Szenario
[cont.]

## Umsetzung
[cont.]

### Hardware
* HoloLens (_"Facehugger"_)
  * Erhält Input von User und Server
  * Sendet Befehle an Server
* Server (_"Sherman"_)
  * Zentrale Rechenkompetenz mit der Aufgabe, Flächen in Punktwolken zu erkennen und diese an die HoloLens weiterzuleiten
  * Sendet Steuerbefehle an Drohne
* Drohne
  * Intel RealSense [R200](https://ark.intel.com/de/products/92256/Intel-RealSense-Camera-R200)
    * Nimmt Kamerabild auf und extrahiert Tiefeninformationen
  * Intel SoC ["AAEON UP"](https://software.intel.com/en-us/realsense/robotic-development-kit) (_"HAL9000"_)
    * Leitet Daten der R200 an Server weiter
    * _(Momentan auf dem Server virtualisiert da nicht verfügbar)_
  * Raspberry Pi 3 (_"Skymaster"_)
    * Leitet Steuerbefehle vom Server an CC3D weiter
  * CC3D
    * Steuert Motoren an
    * Ermöglicht Austarrieren der Drohne

### Software

## Entwicklung
Für die Entwicklung der Software wird diese Github-Repository verwendet. Jedes Software-System erhält seinen eigenen Branch für die Entwicklung, am Ende des Projektes werden diese gemerged.
Vorhandene Branches:
* [HoloLens-Template](https://github.com/mre-lecture/Game-of-Drones/tree/hololens-template) - Bootstrap-Branch zum schnellen Erstellen neuer HoloLens-Anwendungen

[cont.]

### Probleme
* MRE
  * IDE: Gleichzeitige Installation von Visual Studio 2015, Visual Studio 2017 und Unity fürhte dazu, dass sich keine Solutions mehr laden ließen
  * HoloLens-Emulator: Installation konnte installiertes Visual Studio 2015 nicht finden, brach ab
  * Git: Fehlerhafte .gitignore führte dazu, dass alle *.meta-Dateien des Unity-Projekts ignoriert wurden und von der Repository gepullte Projekte nicht korrekt funktionierten
  * Github: Langsame Downloadraten (10kbit/s) von Github führten zu stundenlangen clone- und push-Vorgängen
* ROB
  * Virtualisierung des Intel SoC
      * qemu stürzte ununterbrochen ab
      * qemu-kvm unterstützte keine 64bit-Architektur
      * VirtualBox wurde genutzt, ließ sich zunächst nicht bei Systemboot [des Servers] starten
      * Die Leistung der VM auf die des SoC zu drosseln gelang nur mäßig, mit Herausforderungen bei der Integration des SoC ist zu rechnen
  * 3D-Kameras
    * R200
      * Treiber mussten kompiliert und Secure Boot dafür deaktiviert werden
      * Benötigt USB 3; kann nicht mit Raspberry Pis zu betrieben werden
      * Erkennt reflektierende Flächen nur schlecht
    * SR300
      * Zu groß, schwer und zu geringe "Sichtweite" für Einsatz auf der Drohne
    * Microsoft Kinect
      * Zu groß, schwer und zu großer Stromverbrauch für Einsatz auf der Drohne

_And there are more yet to come..._
