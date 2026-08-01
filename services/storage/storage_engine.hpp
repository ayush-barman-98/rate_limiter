class StorageEngine{
    public:
    virtual ~StorageEngine() {};
    virtual string get(const string& key) = 0;
    virtual void set(const string& key, const string& value) = 0;
    virtual void remove(const string& key) = 0;
}
