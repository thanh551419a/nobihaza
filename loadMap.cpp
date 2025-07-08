#include "loadMap.h";
#include "globalVal.h"
#include <fstream>;
USING_NS_CC;

LoadMap* LoadMap::createFromFile(const std::string& filename) {
    LoadMap* map = new(std::nothrow) LoadMap();
    if (map && map->initFromFile(filename)) {
        map->autorelease();
        return map;
    }
    CC_SAFE_DELETE(map);
    return nullptr;
}

auto gV = globalVal::getInstance();// Khởi tạo biến toàn cục để truy cập các giá trị chung

void LoadMap::reverseRows(std::vector<std::vector<int>>& matrix) {
    std::reverse(matrix.begin(), matrix.end());
}

bool LoadMap::initFromFile(const std::string& filename) {
    std::ifstream file(FileUtils::getInstance()->fullPathForFilename(filename));
    if (!file.is_open()) {
        /*  CCLOG("Không thể mở file %s", filename.c_str());*/
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int val;
        std::vector<int> row;
        while (iss >> val) {
            row.push_back(val);
        }
        mapMatrix.push_back(row);
    }
    reverseRows(mapMatrix);
    gV->setSizeMap(mapMatrix[0].size());
    CCLOG("Kich thuoc map: %d", gV->getSizeMap());
    CCLOG("%d", mapMatrix[0][0]);
    this->scheduleUpdate();  // Luôn update mỗi frame
    return true;
}
void LoadMap::update(float dt) {
	this->removeAllChildren(); // Xóa tất cả các sprite đã render trước đó
    // Cập nhật logic của bản đồ tại đây nếu cần
    // Ví dụ: kiểm tra va chạm, cập nhật trạng thái, v.v.
    // Hiện tại chỉ là một hàm trống để có thể mở rộng sau này




   
	
    
    
    gV->setTileSize((Sprite::create("./PHOTO/Map/duong.png"))->getContentSize().width); // đặt kích thước cho biến tileSize trong globalVal
	auto tileSize = gV->getTileSize();// lấy kích thước 1 block 
    
    
    playerPosX = gV->getPlayerPosX(); // Cập nhật vị trí người chơi nếu cần
    playerPosY = gV->getPlayerPosY(); // Cập nhật vị trí người chơi nếu cần
    //buoc 1: xac dinh o bat dau
	//=> o bat dau la (x1 - 1, y1);
    int x = playerPosX / tileSize - 4;     // Tính toán tọa độ ô bắt đầu theo trục x
    int y = playerPosY / tileSize - 4;     // Tính toán tọa độ ô bắt đầu theo trục y
    int width = 9;                 // Số cột cần render
    int height = 9;                // Số hàng cần render


	
  
    Vec2 startBlock = Vec2(x, y);

	//buoc 2: lech trai lech duoi
    auto leftOffset = playerPosX % tileSize;
	auto bottomOffset = playerPosY % tileSize;
    auto addX = 0 ,addY = 0;

    //buoc 3: bao nhieu o render
    if (leftOffset == 0) addX = 0;
	else addX = 1;
    if (bottomOffset == 0) addY = 0;
    else addY = 1;
    //buoc 4: renderaaaa
    auto renderBlock = 0;

    width += addX;
    height += addY;
    renderBlock = width * height;
   
    for (int i = x; i <= x + width - 1; i++) {//x la toa do tung cua o bat dau
        for (int j = y; j <= y + height - 1; j++) {// y la toa do hoanh cua o bat dau 
            if(i< 0 || i >= mapMatrix[0].size() || j < 0 || j >= mapMatrix.size()) {
                continue; // Bỏ qua nếu vượt quá kích thước ma trận
			}
            int tile = mapMatrix[j][i];
			//CCLOG("Tile at (%d, %d): %d", i, j, tile); // In ra giá trị của ô để kiểm tra
            Sprite* tileSprite = nullptr;
            if (tile == 1) {
              tileSprite = Sprite::create("./PHOTO/Map/sanTruong.png");
            }
            else if (tile == 2) {
               tileSprite = Sprite::create("./PHOTO/Map/viahe.png");
            }
            else if (tile == 3) {
               tileSprite = Sprite::create("./PHOTO/Map/duong.png");
            }
            if (tileSprite) {
                tileSprite->setAnchorPoint(Vec2::ZERO);
                tileSprite->setPosition(Vec2((i - x) * gV->getTileSize() - leftOffset + 175,
                    (j - y) * gV->getTileSize() - bottomOffset));
               // CCLOG("%d", /(i - x) tileSize /- lechTrai +int(GlobalVariables::getInstance()->getHorizontal()));
               this->addChild(tileSprite);
            }
        }
    }

    // In ra thông tin để kiểm tra
    CCLOG("Start Block: (%f, %f)", startBlock.x, startBlock.y);

    //("Left Offset: %d, Bottom Offset: %d", leftOffset, bottomOffset);
	CCLOG("Render Blocks: %d, Width: %d, Height: %d", renderBlock, width, height);


}












