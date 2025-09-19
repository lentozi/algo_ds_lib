//
// Created by LengTouZai on 2025/9/19.
//

#include "base/set_structure.h"
#include "gtest/gtest.h"

TEST(UnionFindSetTest, BasicOperations) {
    // 假设 UnionFindSet 定义在 base/set_structure.h 中，类名为 UnionFindSet
    SetStructure<char> *ufs = new UnionFindSet<char>("TestSet");

    // 初始时，每个元素自成一集
    const std::vector elements = {'a', 'b', 'c', 'd', 'e'};
    dynamic_cast<UnionFindSet<char>*>(ufs)->make_set(elements);

    // 合并一些集合
    dynamic_cast<UnionFindSet<char>*>(ufs)->union_set('a', 'b');
    dynamic_cast<UnionFindSet<char>*>(ufs)->union_set('b', 'c');

    EXPECT_EQ(dynamic_cast<UnionFindSet<char>*>(ufs)->find_root('b'), dynamic_cast<UnionFindSet<char>*>(ufs)->find_root('c'));
    EXPECT_EQ(dynamic_cast<UnionFindSet<char>*>(ufs)->find_root('a'), dynamic_cast<UnionFindSet<char>*>(ufs)->find_root('c'));

    // 检查未合并的元素
    EXPECT_NE(dynamic_cast<UnionFindSet<char>*>(ufs)->find_root('b'), dynamic_cast<UnionFindSet<char>*>(ufs)->find_root('d'));
    EXPECT_NE(dynamic_cast<UnionFindSet<char>*>(ufs)->find_root('b'), dynamic_cast<UnionFindSet<char>*>(ufs)->find_root('e'));

    // 再合并
    dynamic_cast<UnionFindSet<char>*>(ufs)->union_set('c', 'd');
    EXPECT_EQ(dynamic_cast<UnionFindSet<char>*>(ufs)->find_root('b'), dynamic_cast<UnionFindSet<char>*>(ufs)->find_root('d'));

    delete ufs;
}
