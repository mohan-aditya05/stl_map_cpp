#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <stdexcept>

namespace cs440
{
    template<typename Key_T, typename Mapped_T>
    class Map
    {
        private:
        class SkipList;
        SkipList *list;
        typedef std::pair<const Key_T, Mapped_T> ValueType;

        class SentinelNode
        {
            public:
            int level;
            std::vector<SentinelNode *> forward_ptrs;
            SentinelNode *prev;
            SentinelNode(int level)
            {
                this->level = level;
                for(int i=0; i <= level; i++)
                {
                    forward_ptrs.emplace_back(nullptr);
                }
                prev = nullptr;
            }
            virtual ~SentinelNode() = default; 
        };

        class SkipListNode: public SentinelNode
        {
            public:
            // Key_T key;
            // Mapped_T value;
            ValueType data;

            SkipListNode (ValueType tup, int level): SentinelNode(level), data(tup)
            {}
        };

        class SkipList
        {
            private:
            double probability;
            int maxLevel;
            int curr_level;
            
            public:
            SentinelNode *head;
            SentinelNode *tail;
            size_t used_size;

            SkipList()
            {
                probability = 0.5;
                maxLevel = 16;
                used_size = 0;
                curr_level = 0;

                head = new SentinelNode(maxLevel);
                tail = new SentinelNode(maxLevel);
                tail->prev = head;

                for(size_t i = 0; i<=head->forward_ptrs.size(); ++i)
                {
                    head->forward_ptrs[i] = tail;
                }
            }

            ~SkipList()
            {
                used_size = 0;
                SentinelNode *temp = head;
                while(temp!=nullptr)
                {
                    SentinelNode *next = temp->forward_ptrs[0];
                    delete temp;
                    temp = next;
                }
            }

            int randomLevel()
            {
                int l = 0;

                while (((double)std::rand() / RAND_MAX) < probability && l < maxLevel)
                {
                    l++;
                }
                return l;
            }

            SentinelNode *search(Key_T k)
            {
                SentinelNode *temp = head;
                int currMax = this->curr_level;

                for(int i = currMax; i>=0; i--)
                {
                    while(temp->forward_ptrs[i]!=tail && temp->forward_ptrs[i] != nullptr && static_cast<SkipListNode *>(temp->forward_ptrs[i])->data.first < k)
                    {
                        temp = temp->forward_ptrs[i];
                    }
                }
                temp = temp->forward_ptrs[0];

                if(temp!= head && temp!=tail && temp!=nullptr)
                if(static_cast<SkipListNode *>(temp)->data.first == k)
                    return temp;

                return nullptr;
            }

            std::pair<SentinelNode*, bool> insert(ValueType tup)
            {
                SentinelNode *temp = nullptr;
                // temp = search(tup.first);
                std::vector<SentinelNode *> update(head->forward_ptrs);
                int currMax = this->curr_level;
                temp = head;

                for(int i = currMax; i>=0; i--)
                {
                    while(temp->forward_ptrs[i] != nullptr && temp->forward_ptrs[i]!=tail && static_cast<SkipListNode *>(temp->forward_ptrs[i])->data.first < tup.first)
                    {
                        temp = temp->forward_ptrs[i];
                    }
                    update[i] = temp;
                }
                temp = temp->forward_ptrs[0];

                if(temp!= head && temp!=tail && temp!=nullptr)
                if(static_cast<SkipListNode *>(temp)->data.first == tup.first)
                {
                    std::pair<SentinelNode*, bool>res{temp,false};
                    return res;
                }
                SentinelNode *prev = update[0];

                int new_level = 0;
                new_level = randomLevel();
                if(new_level > maxLevel)
                    new_level = maxLevel;

                if(new_level > curr_level)
                {
                    for(int i=curr_level + 1; i <= new_level; ++i)
                    {
                        update[i] = head;
                    }
                    curr_level = new_level;
                }
                temp = new SkipListNode(tup, new_level);

                for(int i=0; i<=new_level; i++)
                {
                    if(update[i] == tail)
                    {
                        temp->forward_ptrs[i] = tail;
                    }
                    else 
                    {
                        temp->forward_ptrs[i] = update[i]->forward_ptrs[i];
                        update[i]->forward_ptrs[i] = temp;
                    }
                }

                temp->prev = prev;
                if(temp->forward_ptrs[0] == tail)
                    tail->prev = temp;
                else
                    temp->forward_ptrs[0]->prev = temp;
                    
                used_size++;
                std::pair<SentinelNode*, bool>res{temp, true};
                return res;
            }

            void erase(Key_T k)
            {
                std::vector<SentinelNode *> update(head->forward_ptrs);
                SentinelNode *temp=head;
                int curr_max = curr_level;
                
                for(int i = curr_max; i >= 0; i--)
                {
                    while(temp->forward_ptrs[i]!=tail && temp->forward_ptrs[i] != nullptr && static_cast<SkipListNode *>(temp->forward_ptrs[i])->data.first < k)
                    {
                        temp = temp->forward_ptrs[i];
                    }
                    update[i] = temp;
                }
                temp = temp->forward_ptrs[0];
                
                if(temp!= tail && static_cast<SkipListNode *>(temp)->data.first == k)
                {
                    for(int i = 0; i <= curr_level; ++i)
                    {
                        if(update[i]->forward_ptrs[i] != temp)
                            break;
                        update[i]->forward_ptrs[i] = temp->forward_ptrs[i];
                    }
                    temp->forward_ptrs[0]->prev = temp->prev;
                    delete temp;
                    while(curr_level > 0 && update[curr_level] == tail)
                    {
                        curr_level--;
                    }
                    used_size--;
                }
                else
                {
                    throw std::out_of_range("Key not found");
                }
            }

        };
        public:
        class Iterator;
        class ConstIterator;
        class ReverseIterator;

        Map()
        {
            list = new SkipList;
        }

        Map(const Map &map_obj)
        {
            list = new SkipList;
            for(auto it = map_obj.begin(); it!=map_obj.end(); it++)
            {
                list->insert(*it);
            }
        }

        Map &operator=(const Map &map_obj)
        {
            delete(list);
            list = new SkipList;
            for(auto it = map_obj.begin(); it!=map_obj.end(); it++)
            {
                list->insert(*it);
            }
            return *this;
        }

        Map (std::initializer_list<ValueType> init_ls)
        {
            list = new SkipList;
            for(auto it = init_ls.begin(); it!=init_ls.end(); it++)
            {
                list->insert(*it);
            }
        }

        ~Map()
        {
            delete list;
        }

        size_t size() const
        {
            return list->used_size;
        }

        bool empty() const
        {
            if(size() == 0)
                return true;
            return false;
        }
        Iterator begin()
        {
            Iterator it(list->head->forward_ptrs[0]);
            return it;
        }

        Iterator end()
        {
            Iterator it(list->tail);
            return it;
        }
        ConstIterator begin() const
        {
            ConstIterator it(list->head->forward_ptrs[0]);
            return it;
        }

        ConstIterator end() const
        {
            ConstIterator it(list->tail);
            return it;
        }
        
        ReverseIterator rbegin()
        {
            ReverseIterator it(list->tail->prev);
            return it;
        }

        ReverseIterator rend()
        {
            ReverseIterator it(list->head);
            return it;
        }

        std::pair<Iterator, bool> insert(const ValueType& kv)
        {
            std::pair<SentinelNode *, bool>res;
            res = list->insert(kv);
            Iterator it(res.first);
            bool search_flag = res.second;

            std::pair<Iterator, bool>response{it, search_flag};
            return response;
        }

        template<typename IT_T>
        void insert(IT_T range_beg, IT_T range_end)
        {
            for(auto i = range_beg; i!=range_end; i++)
            {
                insert(i);
            }
        }

        Mapped_T& at(const Key_T& k)
        {
            SentinelNode *node = list->search(k);
            if(node)
            {
                return static_cast<SkipListNode *>(node)->data.second;
            }
            else
            {
                throw std::out_of_range("Key not found");
            }
        }

        const Mapped_T& at(const Key_T& k) const
        {
            SentinelNode *node = list->search(k);
            if(node)
            {
                return static_cast<SkipListNode *>(node)->data.second;
            }
            else
            {
                throw std::out_of_range("Key not found");
            }
        }

        Iterator find(const Key_T& k)
        {
            SentinelNode *node = list->search(k);
            if(node)
            {
                Iterator it(node);
                return it;
            }
            else
            {
                return end();
            }
        }

        ConstIterator find(const Key_T& k) const
        {
            SentinelNode *node = list->search(k);
            if(node)
            {
                ConstIterator it(node);
                return it;
            }
            else
            {
                return end();
            }
        }

        void erase(Iterator pos)
        {
            if(pos.curr_node)
            {
                Key_T k = (*pos).first;
                list->erase(k);
            }
        }

        void erase(const Key_T& k)
        {
            list->erase(k);
        }

        void clear()
        {
            delete list;
            list = new SkipList;
        }

        // Added this function to test the behaviour of the previous node ptr in every node.
        /*
        void print()
        {
            SkipListNode *temp = list->head->forward_ptrs[0];
            int node_num = 1;
            std::cout<<"temp: "<<temp<<" tail: "<<list->tail<<std::endl;
            while(temp!=list->tail)
            {
                std::cout<<"Node: "<<node_num<<std::endl;
                std::cout<<"Curr Addr:"<<temp<<std::endl;
                std::cout<<"Prev Addr:"<<temp->prev<<std::endl;
                std::cout<<"Key:"<<temp->key<<" Value:"<<temp->value<<std::endl;
                std::cout<<"**********************************"<<std::endl;

                temp = temp->forward_ptrs[0];
                node_num++;
            }
        }
        */

        Mapped_T& operator[](Key_T k)
        {
            SentinelNode *res = list->search(k);
            if(res == nullptr)
            {
                list->insert(std::make_pair(k, Mapped_T()));
                res = list->search(k);
            }

            return static_cast<SkipListNode *>(res)->data.second;
        }

        friend bool operator==(const Map& m1, const Map& m2)
        {
            if(m1.size() != m2.size())
                return false;
            else
            {
                auto it1 = m1.begin();
                auto it2 = m2.begin();

                auto it1_end = m1.end();
                auto it2_end = m2.end();
                
                int true_count = m1.size();
                while(((*it1).first == (*it2).first) && ((*it1).second == (*it2).second))
                {
                    ++it1;
                    ++it2;
                    --true_count;
                    if(it1 == it1_end || it2 == it2_end)
                        break;
                }
                if(true_count !=0)
                    return false;
            }
            return true;
        }

        friend bool operator!=(const Map& m1, const Map& m2)
        {
            if(m1.size() != m2.size())
                return true;
            else
            {
                auto it1 = m1.begin();
                auto it2 = m2.begin();

                auto it1_end = m1.end();
                auto it2_end = m2.end();
                
                int false_count = m1.size();
                while(((*it1).first != (*it2).first) || ((*it1).second != (*it2).second))
                {
                    ++it1;
                    ++it2;
                    --false_count;
                    if(it1 == it1_end || it2 == it2_end)
                        break;
                }
                // std::cout<<"False Count: "<<false_count<<std::endl;
                if(false_count != 0)
                    return false;
            }
            return true;
        }

        friend bool operator<(const Map& m1, const Map& m2)
        {
            auto it1 = m1.begin();
            auto it2 = m2.begin();

            auto it1_end = m1.end();
            auto it2_end = m2.end();

            size_t elem_equal = 0;

            while (it1 != it1_end && it2 != it2_end)
            {
                if((*it1) > (*it2))
                {
                    return false;
                }
                else if ((*it1) == (*it2))
                {
                    ++elem_equal;
                }

                ++it1;
                ++it2;
            }

            size_t s1 = m1.size();
            size_t s2 = m2.size();

            if(elem_equal == s1)
            {
                if(s1 < s2)
                    return true;
                return false;
            }

            return true;
        }

        class Iterator
        {
            public:
            SentinelNode *curr_node;

            Iterator() = delete;    

            Iterator(SentinelNode *node)
            {
                curr_node = node;
            }

            Iterator(const Iterator &it)
            {
                curr_node = it.curr_node;
            }
            
            Iterator& operator=(const Iterator &obj)
            {
                curr_node = obj.curr_node;
                return *this;
            }
            
            Iterator& operator++()
            {
                curr_node = curr_node->forward_ptrs[0];
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator &it = *this;
                curr_node = curr_node->forward_ptrs[0];
                return it;
            }
            Iterator& operator--()
            {
                curr_node = curr_node->prev;
                return *this;
            }

            Iterator operator--(int)
            {
                Iterator &it = *this;
                curr_node = curr_node->prev;
                return it;
            }

            ValueType& operator*() const
            {
                return static_cast<SkipListNode *>(curr_node)->data;
            }

            ValueType* operator->() const
            {
                return &(static_cast<SkipListNode *>(curr_node)->data);
            }

            friend bool operator==(const Iterator &it1, const Iterator &it2)
            {
                if (it1.curr_node == it2.curr_node)
                    return true;
                return false;
            }

            friend bool operator==(const Iterator &it1, const ConstIterator &it2)
            {
                if (it1.curr_node == it2.curr_node)
                    return true;
                return false;
            }

            friend bool operator==(const ConstIterator &it1, const Iterator &it2)
            {
                if (it1.curr_node == it2.curr_node)
                    return true;
                return false;
            }

            friend bool operator!=(const Iterator &it1, const Iterator &it2)
            {
                if (it1.curr_node != it2.curr_node)
                    return true;
                return false;
            }

            friend bool operator!=(const Iterator &it1, const ConstIterator &it2)
            {
                if (it1.curr_node != it2.curr_node)
                    return true;
                return false;
            }

            friend bool operator!=(const ConstIterator &it1, const Iterator &it2)
            {
                if (it1.curr_node != it2.curr_node)
                    return true;
                return false;
            }

        };
        class ConstIterator
        {
            public:
            SentinelNode *curr_node;
            
            ConstIterator() = delete;

            ConstIterator(SentinelNode *node)
            {
                curr_node = node;
            }
            ConstIterator(const Iterator &it)
            {
                curr_node = it.curr_node;
            }

            ConstIterator& operator++()
            {
                curr_node = curr_node->forward_ptrs[0];
                return *this;
            }

            ConstIterator operator++(int)
            {
                ConstIterator &it = *this;
                curr_node = curr_node->forward_ptrs[0];
                return it;
            }
            ConstIterator& operator--()
            {
                curr_node = curr_node->prev;
                return *this;
            }

            ConstIterator operator--(int)
            {
                ConstIterator &it = *this;
                curr_node = curr_node->prev;
                return it;
            }

            ConstIterator& operator=(const ConstIterator &obj)
            {
                curr_node = obj.curr_node;
                return *this;
            }
            const ValueType& operator*() const
            {
                return static_cast<SkipListNode *>(curr_node)->data;
            }

            const ValueType* operator->() const
            {
                return &(static_cast<SkipListNode *>(curr_node)->data);
            }
            friend bool operator==(const ConstIterator &it1, const ConstIterator &it2)
            {
                if (it1.curr_node == it2.curr_node)
                    return true;
                return false;
            }

            friend bool operator!=(const ConstIterator &it1, const ConstIterator &it2)
            {
                if (it1.curr_node != it2.curr_node)
                    return true;
                return false;
            }
        };

        class ReverseIterator
        {
            public:
            SentinelNode *curr_node;
            ReverseIterator() = delete;

            ReverseIterator(SentinelNode *node)
            {
                curr_node = node;
            }
            ReverseIterator(const Iterator &it)
            {
                curr_node = it.curr_node;
            }

            ReverseIterator& operator++()
            {
                curr_node = curr_node->prev;
                return *this;
            }

            ReverseIterator operator++(int)
            {
                ReverseIterator &it = *this;
                curr_node = curr_node->prev;
                return it;
            }
            ReverseIterator& operator--()
            {
                curr_node = curr_node->forward_ptrs[0];
                return *this;
            }

            ReverseIterator operator--(int)
            {
                ReverseIterator &it = *this;
                curr_node = curr_node->forward_ptrs[0];
                return it;
            }

            ReverseIterator& operator=(const ReverseIterator &obj)
            {
                curr_node = obj.curr_node;
                return *this;
            }
            ValueType& operator*() const
            {
                return static_cast<SkipListNode *>(curr_node)->data;
            }

            ValueType* operator->() const
            {
                return &(static_cast<SkipListNode *>(curr_node)->data);
            }

            friend bool operator==(const ReverseIterator &it1, const ReverseIterator &it2)
            {
                if (it1.curr_node == it2.curr_node)
                    return true;
                return false;
            }

            friend bool operator!=(const ReverseIterator &it1, const ReverseIterator &it2)
            {
                if (it1.curr_node != it2.curr_node)
                    return true;
                return false;
            }
        };
    };
}

#endif