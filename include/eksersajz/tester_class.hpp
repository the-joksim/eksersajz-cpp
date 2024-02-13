class Tester final {
public:
  Tester();
  ~Tester();

  Tester(const Tester &other);
  Tester &operator=(const Tester &other);

  Tester(Tester &&other);
  Tester &operator=(Tester &&other);
};
