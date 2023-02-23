
#define MsgClose() WM_CLOSE, 0, 0
#define MsgLButtonDown(keys, x, y) WM_LBUTTONDOWN, keys, MAKE32(x, y)
#define MsgLButtonUp(keys, x, y) WM_LBUTTONUP, keys, MAKE32(x, y)
#define MsgMenuCommand(menuId) WM_COMMAND, MAKELONG(menuId, 0), 0