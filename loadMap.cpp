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
    globalVal::getInstance()->setSizeMap(mapMatrix[0].size());
//    CCLOG("Kich thuoc map: %d", gV->getSizeMap());
 //   CCLOG("%d", mapMatrix[0][0]);
    this->scheduleUpdate();  // Luôn update mỗi frame
    return true;
}
void LoadMap::update(float dt) {
	this->removeAllChildren(); // Xóa tất cả các sprite đã render trước đó
    // Cập nhật logic của bản đồ tại đây nếu cần
    // Ví dụ: kiểm tra va chạm, cập nhật trạng thái, v.v.
    // Hiện tại chỉ là một hàm trống để có thể mở rộng sau này
	gV = globalVal::getInstance();
    auto sprite = Sprite::create("/PHOTO/Map/duong.png");
    if (sprite == nullptr) {
      //  CCLOG("Failed to load image /PHOTO/Map/duong.png");
        // Xử lý lỗi, ví dụ đặt tileSize mặc định hoặc thoát
        gV->setTileSize(32); // ví dụ kích thước mặc định
    }
    else {
        gV->setTileSize(sprite->getContentSize().width);
    }
    tileSize = gV->getTileSize();// lấy kích thước 1 block 
    
    frameSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
	int sizeMap = gV->getSizeMap(); // Lấy kích thước bản đồ từ globalVal
    playerPosX = gV->getPlayerPosX(); // Cập nhật vị trí người chơi nếu cần
    playerPosY = gV->getPlayerPosY(); // Cập nhật vị trí người chơi nếu cần
    //buoc 1: xac dinh o bat dau
	//=> o bat dau la (x1 - 1, y1);
	//CCLOG("do rong cua : %f %f", frameSize.width, frameSize.height);
    width = frameSize.height / tileSize;                 // Số cột cần render
    height = frameSize.height / tileSize;                // Số hàng cần render
	//CCLOG("Width: %d, Height: %d", width, height);
    // xu ly vi tri nhan vat theo chieu doc
    if (playerPosY > tileSize * (sizeMap - height / 2)) {// neu vi tri nhan vat di vao vung nhan vat di chuyen map dung im
		playerPosY = float(tileSize * (sizeMap - height / 2));
    }
    if (playerPosY < tileSize * (height / 2)) { // neu vi tri nhan vat di vao vung nhan vat di chuyen map dung im
		playerPosY = float(tileSize * (height / 2));
    }
	if (playerPosX < tileSize * (width / 2)) { // neu vi tri nhan vat di vao vung nhan vat di chuyen map dung im
        playerPosX = float(tileSize * (width / 2));
	}
	if (playerPosX > tileSize * (sizeMap - width / 2)) { // neu vi tri nhan vat di vao vung nhan vat di chuyen map dung im
		playerPosX = float(tileSize * (sizeMap - width / 2));
	}
    CCLOG("Player Position: %f %f", gV->getPlayerPosX(), playerPosY);
   // CCLOG("%d %d %d", tileSize, sizeMap, height);
  //  CCLOG("size: %d", tileSize * (sizeMap - height / 2));
	//CCLOG("Tile Size: %d", tileSize);
 //   CCLOG("Frame Size: %f %f", frameSize.width, frameSize.height);
    int x = playerPosX / tileSize - width/2 ;     // Tính toán tọa độ ô bắt đầu theo trục x
    int y = playerPosY / tileSize - width/2;     // Tính toán tọa độ ô bắt đầu theo trục y
    Vec2 startBlock = Vec2(x, y);

	//buoc 2: lech trai lech duoi
    auto leftOffset = int(playerPosX) % tileSize;
	auto bottomOffset = int(playerPosY) % tileSize;
    auto addX = 0 ,addY = 0;
    
    //buoc 3: bao nhieu o renderx
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
              tileSprite = Sprite::create("/PHOTO/Map/sanTruong.png");
            }
            else if (tile == 2) {
               tileSprite = Sprite::create("/PHOTO/Map/viahe.png");
            }
            else if (tile == 3) {
               tileSprite = Sprite::create("/PHOTO/Map/duong.png");
            }
            if (tileSprite) {
                tileSprite->setAnchorPoint(Vec2::ZERO);
                tileSprite->setPosition(Vec2((i - x) * gV->getTileSize() - leftOffset + (frameSize.width - frameSize.height) / 2,
                    (j - y) * gV->getTileSize() - bottomOffset));
               // CCLOG("%d", /(i - x) tileSize /- lechTrai +int(GlobalVariables::getInstance()->getHorizontal()));
               this->addChild(tileSprite);
            }
        }
    }

    // In ra thông tin để kiểm tra
    //CCLOG("Start Block: (%f, %f)", startBlock.x, startBlock.y);
    //("Left Offset: %d, Bottom Offset: %d", leftOffset, bottomOffset);
	//CCLOG("Render Blocks: %d, Width: %d, Height: %d", renderBlock, width, height);
}












