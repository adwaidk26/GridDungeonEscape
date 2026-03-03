Name:           griddungeonescape
Version:        0.0.1
Release:        1
Summary:        Grid-based dungeon puzzle game built with raylib
License:        Proprietary
Group:          Games
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  gcc-c++
BuildRequires:  pkgconfig(raylib)

%description
GridDungeonEscape is a grid-based dungeon puzzle game written in C++ with
raylib.

%prep
%setup -q

%build
cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DGAME_DATA_DIR=%{_datadir}/GridDungeonEscape
cmake --build build

%install
rm -rf %{buildroot}

install -d %{buildroot}%{_bindir}
install -m 0755 build/GridDungeonEscape %{buildroot}%{_bindir}/GridDungeonEscape

install -d %{buildroot}%{_datadir}/GridDungeonEscape/Images
install -d %{buildroot}%{_datadir}/GridDungeonEscape/Maps
install -m 0644 Game/Res/Images/* %{buildroot}%{_datadir}/GridDungeonEscape/Images/
install -m 0644 Game/Res/Maps/* %{buildroot}%{_datadir}/GridDungeonEscape/Maps/

%files
%{_bindir}/GridDungeonEscape
%dir %{_datadir}/GridDungeonEscape
%dir %{_datadir}/GridDungeonEscape/Images
%dir %{_datadir}/GridDungeonEscape/Maps
%{_datadir}/GridDungeonEscape/Images/*
%{_datadir}/GridDungeonEscape/Maps/*

%changelog
- Initial RPM packaging for gbs build
