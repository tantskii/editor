#include "controller.h"

/*!
 Оповещение графическим примитивов контроллера о своем действии.
 @param modelPtr Указатель на документ.
 @param event Событие.
 */
void Controller::notify(IModelPtr modelPtr, std::string event) const {
    UNUSED(modelPtr);
    
    std::cout << "[Controller] " << event << std::endl;
}


/*!
 Создание графического примитива.
 @return Указатель на графический примитив.
 */
GraphicPrimitivePtr Controller::createGraphicPrimitive() {
    m_graphicPrimitivePtr = std::make_shared<GraphicPrimitive>();
    m_graphicPrimitivePtr->setController(shared_from_this());
    notify(m_graphicPrimitivePtr, "create graphic primitive");
    return m_graphicPrimitivePtr;
}


/*!
 Удаление графического примитива.
 @param graphicPrimitivePtr Указатель на удаляемый графический примитив.
 */
void Controller::destroyGraphicPrimitive(GraphicPrimitivePtr graphicPrimitivePtr) {
    if (graphicPrimitivePtr == m_graphicPrimitivePtr) {
        m_graphicPrimitivePtr.reset();
    }
}

/*!
 Создание документа.
 @return Указатель на документ.
 */
DocumentPtr Controller::createDocument() {
    m_documentPtr = std::make_shared<Document>();
    m_documentPtr->setController(shared_from_this());
    notify(m_documentPtr, "create document");
    return m_documentPtr;
}


/*!
 Создание представления документа.
 */
DocumentViewPtr Controller::createDocumentView() {
    DocumentViewPtr view = std::make_shared<DocumentView>();
    view->setModel(m_documentPtr);
    m_documentPtr->attach(view);
    return view;
}


/*!
 Создание представления графического примитива.
 */
GraphicPrimitiveViewPtr Controller::createGraphicPrimitiveView() {
    GraphicPrimitiveViewPtr view = std::make_shared<GraphicPrimitiveView>();
    view->setModel(m_graphicPrimitivePtr);
    m_graphicPrimitivePtr->attach(view);
    return view;
}


ControllerPtr makeController() {
    return std::make_shared<Controller>();
}

