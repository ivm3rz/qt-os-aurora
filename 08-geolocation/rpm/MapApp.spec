Name:       MapApp
Summary:    Демо-приложение, работающее с картой в ОС Аврора
Version:    0.1
Release:    1
Group:      Qt/Qt
License:    BSD-3-Clause
Source0:    %{name}-%{version}.tar.bz2

Requires:   sailfishsilica-qt5 >= 0.10.9
Requires:   qt5-qtdeclarative-import-positioning
# ToDo: add requires to use QtLocation with OSM plugin in QML
# ToDo: add requires to use WebTiles
BuildRequires: cmake

%description
Демо-приложение, работающее с картой в ОС Аврора

%prep
%autosetup

%build
%cmake
%make_build

%install
%make_install

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%defattr(644,root,root,-)
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
