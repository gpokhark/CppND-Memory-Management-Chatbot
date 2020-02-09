#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////
    // Remove this for Task 0
    // if (_chatBot != NULL) {
    //     std::cout << "Graph node destructor." << std::endl;
    //     delete _chatBot; 
    // }
    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

// void GraphNode::AddEdgeToChildNode(GraphEdge *edge)
void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> &&edge)
{
    // Task 4 part 1 exclusive ownership of child edges to graphnode
    // _childEdges.push_back(edge);
    // _childEdges.push_back(std::unique_ptr<GraphEdge>(edge));
    _childEdges.push_back(std::move(edge));

}

//// STUDENT CODE
////
// void GraphNode::MoveChatbotHere(ChatBot *chatbot)
void GraphNode::MoveChatbotHere(ChatBot &&chatbot)
{
    _chatBot = ChatBot(std::move(chatbot));
    _chatBot.GetChatLogicHandle()->SetChatbotHandle(&_chatBot);
    // _chatBot.SetImageHandle(_chatBot.GetImageHandle()); // Set the image handle to the previous image handle
    _chatBot.SetCurrentNode(this);
    // std::cout << "GraphNode::MoveChatbotHere() After\n";
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    ChatBot tempbot = ChatBot();
    tempbot.SetRootNode(_chatBot.GetRootNode()); // Set the root node
    tempbot.SetChatLogicHandle(_chatBot.GetChatLogicHandle());
    tempbot.SetImageHandle(_chatBot.GetImageHandle());
    newNode->MoveChatbotHere(std::move(tempbot));
    // newNode->MoveChatbotHere(_chatBot);
    _chatBot.SetImageHandle(nullptr);  // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////
    // Task 4 part 1 exclusive ownership of child edges to graphnode
    // return _childEdges[index];
    return _childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}