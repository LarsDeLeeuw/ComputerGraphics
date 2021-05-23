# ComputerGraphics
A graphics engine created for the university course "Computer Graphics" of the University of Antwerp.
## Gequoteerde functionaliteit

V: Werkend  
-: Deels werkend met gekende problemen (onderaan beschreven)  
X: Niet werkend of niet geïmplementeerd  
(blanco): TODO  


|   | Functionaliteit      | Status |
|---|---------------------------|---|
| 1 | 2D L-systemen             |  V |
|   | Met haakjes               | V  |
|   | Stochastisch              |  X |
| 2 | Transformaties            | V  |
|   | Eye-point                 |  V |
|   | Projectie                 |  V |
| 3 | Platonische Lichamen      |  V |
|   | Kegel en cylinder         |  V |
|   | Bol                       | V  |
|   | Torus                     | V  |
|   | 3D L-systemen             | V  |
| 4 | Z-buffering (lijnen)      |  V |
| 5 | Triangulatie              |  V |
|   | Z-buffering (driehoeken)  | V  |
| 6 | 3D fractalen              |  V |
|   | BuckyBall                 |   X|
|   | Mengerspons               | X  |
|   | View Frustum              |  X|
| 7 | Ambient licht             |   X|
|   | Diffuus licht (oneindig)  |  X|
|   | Diffuus licht (puntbron)  |  X|
|   | Speculair licht           |  X|
| 8 | Schaduw                   | X  |
|   | Texture mapping           |  X |
| 9 | Bollen en cylinders       |  X |
|   | UV-coordinaten            |  X |
|   | Cube mapping              |  X |

Geïmplementeerde vorm van texture mapping: ...

## Gekende problemen 

## Niet-gequoteerde functionaliteit
Indien u mijn ZBuffering beter wilt uit testen kan u in het Figure.cpp bestand in

**Figure::draw_zbuf_triangles(ZBuffer &zbuffer, img::EasyImage &image, double d, double dx, double dy)**,

de 3 regels code uncommenten, hierdoor worden de vlakken in afwisselende kleuren getoond.
## Extra functionaliteit, niet in de opgaves beschreven
...
