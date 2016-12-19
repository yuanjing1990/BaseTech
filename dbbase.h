// 定义总属性
#define DECL_MDS_TOTAL_ATTR \
protected: \
	std::map<std::string, TEValue> m_AttrValue; \
	std::set<std::string> m_AttrModifyed; \
	bool IsModifyed(const std::string& attr) const { \
	return m_AttrModifyed.find(attr) != m_AttrModifyed.end(); } \
public: \
	bool IsAnyAttrModifyed() const {return !m_AttrModifyed.empty(); } 



// 定义各属性
#define DECL_MDS_SIMP_ATTR(TYPE, attrname) \
protected: \
	TYPE m_##attrname; \
	void Init##attrname(const TYPE& value) { \
	m_##attrname = value; m_AttrValue[#attrname] = TEValue(value);} \
public: \
	void Set##attrname(const TYPE& value) { \
	m_##attrname = value;   m_upt->setSQLUpdate(Gettable()); m_upt->setSQLSet(#attrname,value); \
	m_ins->setSQLInsert(Gettable());  m_ins->setSQLValues(#attrname,value); (void)m_AttrModifyed.insert(#attrname); m_AttrValue[#attrname] = TEValue(value); } \
	TYPE Get##attrname() const { return m_##attrname; } \
	bool Is##attrname##Modifyed() const {return IsModifyed(#attrname);} \
	static RWDBColumnNew Get##attrname##Column() { \
	RWDBColumnNew col;col.setSQLFrom(Gettable()); col.setSQLColumnTable(Gettable()); col.setSQLColumn(#attrname);   col.setSQLColumn_Last(#attrname); return col;} \
	static TEValue::ValueType Get##attrname##Type() { \
	return TEValue(TYPE()).type();} \
	static RWDBColumnNew Get##attrname##ColumnType() { \
	return Get##attrname##Column();}


#define IMPL_MDS_SIMP_ATTR(classname, tablename, attrname) \
	static InitMdsClassColumn init_##tablename##_##attrname(#tablename, #attrname, classname::Get##attrname##Type());

// MO类必须函数, 加classname这个参数是为了使每个类区分，便于VA插件解析,自动联想每个类的成员函数
#define DECL_MDS_CLASS(classname) \
public: \
	static std::string Gettable(); \
	static RWDBColumnNew AllColumn(); \
	static RWDBColumnNew AllColumnType(); \
	CMdsDBUpdater updater() const; \
	CMdsDBInserter inserter() const; \
	static CMdsDBDeleter deleter();


// 与DECL_MDS_CLASS配套使用
#define IMPL_MDS_CLASS(classname, tablename) \
	static InitMdsClass init_mds_##tablename(#tablename); \
	std::string classname::Gettable(){ \
	return #tablename;}\
	RWDBColumnNew classname::AllColumn() { \
	RWDBColumnNew col; col.setSQLFrom(#tablename);col.setSQLColumnTable(#tablename); col.setSQLColumn("*"); col.setSQLColumn_Last("*");  return col; } \
	RWDBColumnNew classname::AllColumnType() { \
	return classname::AllColumn(); } \
	CMdsDBUpdater classname::updater() const { \
	return *m_upt; } \
	CMdsDBInserter classname::inserter() const {\
	return *m_ins; } \
	CMdsDBDeleter classname::deleter(){ \
	CMdsDBDeleter del;del.setSQLDelete(#tablename); return del; }
