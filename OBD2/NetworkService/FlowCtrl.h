/*
 * FlowCtrl.h
 *
 *  Created on: 2014Äê1ÔÂ10ÈÕ
 *      Author: zezhongzhao
 */

#ifndef FLOWCTRL_H_
#define FLOWCTRL_H_

unsigned char FlowCtrlStart = 0;
enum {
	idle,
	sendFirstFrame,
	waitFlowCtrlFrame,
	sendConsecutiveFrame,
	finishFlow,
}NetworkLayerFlowState;


#endif /* FLOWCTRL_H_ */
