#pragma once
class Tests
{
public:
	Tests() = default;
	~Tests() = default;
	static void testDomain();
	static void testValidator();
	static void testRepoProduse();
	static void testRepoCos();
	static void testService();
	static void testServiceCos();
	static void testMap();
	static void testMap2();
	static void testReadAllFromFile();
	static void testWriteToFile();
	static void testUndo();
};