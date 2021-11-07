class CEffect
{
public:

	float x = 0;
	float y = 0;

	float vx = 0;
	float vy = 0;

	int state = 0;
	//function<void()> callback;
	CEffect(float x, float y);

	virtual void Render() = 0;
	virtual void Update(DWORD dt) = 0;
	/*virtual void Start(function<void()> _callback) {
		this->callback = _callback;
	};*/
	virtual void SetState(int _state) {
		this->state = _state;
	}
	void SetPositionX(float _x) {
		this->x = _x;
	}
	void SetPositionY(float _y) {
		this->y = _y;
	}
	float GetPositionX() {
		return this->x;
	}
	float GetPositionY() {
		return this->x;
	}
};

typedef CEffect* LPEFFECT;