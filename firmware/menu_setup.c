//#include "menu_setup.h"
//
//MENU_ITEM(P0, P1, P1, EXIT, P0UP, NULL, NULL, MENU_P0);
//MENU_ITEM(P1, P0, P0, EXIT, P1UP, NULL, NULL, MENU_P1);
//MENU_ITEM(EXIT, NULL_MENU, NULL_MENU, NULL_MENU, NULL_MENU, NULL, NULL, 0x0);
//MENU_ITEM(P0UP, P0DW, P0DW, P0, NULL_MENU, NULL, NULL, MENU_P0UP);
//MENU_ITEM(P0DW, P0UP, P0UP, P0, NULL_MENU, NULL, NULL, MENU_P0DW);
//MENU_ITEM(P1UP, P1DW, P1DW, P1, NULL_MENU, NULL, NULL, MENU_P1UP);
//MENU_ITEM(P1DW, P1UP, P1UP, P1, NULL_MENU, NULL, NULL, MENU_P1DW);
//
//enum ButtonValues GetButtonPress(void) {
//  return BUTTON_NONE;
//};
//
//void Generic_Write(const uint16_t Text) {
//  if(Text)
//    print_bits(Text);
//}
//
//
///** Example menu item specific enter callback function, run when the associated menu item is entered. */
////static void Level1Item1_Enter(void) {
////  print_bits(67);
////  _delay_us(1000);
////}
//
///** Example menu item specific select callback function, run when the associated menu item is selected. */
////static void Level1Item1_Select(void) {
////  print_bits(94);
////  _delay_us(1000);
////}