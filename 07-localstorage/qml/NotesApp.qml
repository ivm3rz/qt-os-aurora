import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"
import "cover"

ApplicationWindow {
     initialPage: Component { Notes { } }
     cover: Component { CoverPage { } }
}
