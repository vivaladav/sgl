project(libSGui LANGUAGES CXX)

# SDL 2
find_package(SDL2 REQUIRED)

add_library(
    sgui
    include/sgl/sgui/AbstractButton.h
    include/sgl/sgui/AbstractButtonsGroup.h
    include/sgl/sgui/ButtonsGroup.h
    include/sgl/sgui/ComboBox.h
    include/sgl/sgui/ComboBoxItem.h
    include/sgl/sgui/Image.h
    include/sgl/sgui/ImageButton.h
    include/sgl/sgui/Label.h
    include/sgl/sgui/ProgressBar.h
    include/sgl/sgui/PushButton.h
    include/sgl/sgui/Slider.h
    include/sgl/sgui/Stage.h
    include/sgl/sgui/TextArea.h
    include/sgl/sgui/WidgetContainer.h
    include/sgl/sgui/Widget.h
    src/AbstractButton.cpp
    src/AbstractButtonsGroup.cpp
    src/ButtonsGroup.cpp
    src/ComboBox.cpp
    src/ComboBoxItem.cpp
    src/Image.cpp
    src/ImageButton.cpp
    src/Label.cpp
    src/ProgressBar.cpp
    src/PushButton.cpp
    src/Slider.cpp
    src/Stage.cpp
    src/TextArea.cpp
    src/Widget.cpp
    src/WidgetContainer.cpp
)

target_link_libraries(
    sgui
    PUBLIC core
    PUBLIC graphic
)

target_include_directories(
    sgui
    PUBLIC include
)
