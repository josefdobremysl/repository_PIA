Jak spustit
Tento program využívá knihovny allegro5. Instalaci knihovny allegro5 budeme provádět pomocí vcpkg.
Instalace vcpkg
Naklonujte repozitář vcpkg:
git clone https://github.com/Microsoft/vcpkg.git
Nejdříve se ujistěte, že jste v adresáři, do kterého chcete nástroj nainstalovat.
Spusťte zaváděcí skript pro sestavení vcpkg:
V adresáři ve kterém máte nainstalovaný vcpkg, spust´te Powershell a zadejte příkaz .\vcpkg\bootstrap-vcpkg.bat
Nainstalujte knihovny pro svůj projekt, pro nainstalování knihovny allegro5 zadejte příkaz
.\vcpkg install allegro5
Dále zadejte příkaz 
vcpkg integrate install
 v Powershell bude vypsán příkaz, který zkopírujete do Nuget Package Manager Console.
