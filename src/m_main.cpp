export module main;
export
{

//#include <cstddef>
namespace std {using size_t = decltype(sizeof(int));}

    // to ensure that the current game physics are correct, kScreenWidth, kScreenHeight, kGridBlockSize, kBorderWidth, (kScreenWidth / kBlocksPerRow), and (kScreenHeight / kRowsPerGame) should all be evenly divisable by five
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{1000};
    constexpr std::size_t kScreenHeight{700};
    constexpr std::size_t kGridBlockSize{5};
    constexpr std::size_t kGridWidth{kScreenWidth / kGridBlockSize};
    constexpr std::size_t kGridHeight{kScreenHeight / kGridBlockSize};

    // implement additional color cases in renderer.cpp if kRowsPerGame > 8
    constexpr std::size_t kRowsPerGame{8};
    constexpr std::size_t kBlocksPerRow{8};
    constexpr std::size_t kBorderWidth{5};
}