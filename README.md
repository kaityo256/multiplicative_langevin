# Multiplicative Langevin Simulation

## 実行方法

```sh
make
./a.out
gnuplot additive.plt
gnuplot multiplicative.plt
```

## Additive Noise

以下のLangevin方程式を考える。

$$
\dot{x} = -x + \hat{R}
$$

ただし、$\hat{R}$は

$$
\left< \hat{R}(t_1) \hat{R}(t_2)\right> = 2 \delta(t_1-t_2)
$$

を満たす白色雑音である。

ノイズが加法的(additive)な場合、対応するFocker-Planck方程式はIto、Stratonovichともに同じ形になる。

$$
\frac{\partial f}{\partial t} = -\frac{\partial}{\partial x}
\left(
    -xf - \frac{\partial f }{\partial x}
\right)
$$

定常状態は$\partial f_{eq}/\partial t = 0$より、

$$
-xf_{eq} - \frac{\partial f_{eq} }{\partial x} =0
$$

以上から、

$$
f_{eq} = \frac{\mathrm{e}^{-x^2/2}}{\sqrt{2 \pi}}
$$

実際にシミュレーションしてみると、定常状態の分布関数はガウス分布に一致する。数値解法はEuler-Maruyama法を用いた。

![additive.png](additive.png)

## Multiplicative Noise

以下のLangevin方程式を考える。

$$
\dot{x} = -x^3 + x\hat{R}_1 + \hat{R}_2
$$

ただし、$\hat{R}_1,\hat{R}_2$は

$$
\begin{aligned}
\left< \hat{R}_1(t_1) \hat{R}_1(t_2)\right> &= 2 \delta(t_1-t_2) \\
\left< \hat{R}_1(t_1) \hat{R}_1(t_2)\right> &= 2 \delta(t_1-t_2) \\
\left< \hat{R}_1(t_1) \hat{R}_2(t_2)\right> &=0
\end{aligned}
$$

を満たす白色雑音であり、$\hat{R}_2$を加えたのは、$x=0$の時に$\dot{x} = 0$となってしまうのを防ぐためである。

ノイズが乗法的(multiplicative)な場合は、ItoとStratonovichでFocker-Planck方程式の形が変わる。

Stratonovichの場合

$$
\frac{\partial f}{\partial x} =
-\frac{\partial}{\partial x}\left(
-x^3 f - x \frac{\partial}{\partial x} (xf) - \frac{\partial f}{\partial x}
\right
)
$$

定常状態は、

$$
-x^3 f_{eq} - x f_{eq} - (x^2+1)f'_{eq} = 0
$$

より、

$$
f_{eq} = \frac{\mathrm{e}^{-x^2/2}}{\sqrt{2 \pi}}
$$

となる。

Itoの場合、

$$
\frac{\partial f}{\partial x} =
-\frac{\partial}{\partial x}\left(
-x^3 f -\frac{\partial}{\partial x} (x^2f) - \frac{\partial f}{\partial x}
\right
)
$$

定常状態は、

$$
f'_{eq} = -\frac{x^3+2x}{x^2+1} f_{eq}
$$

より、

$$
f_{eq} = C^{-1} \frac{\mathrm{e}^{-x^2/2} }{\sqrt{1+x^2}}
$$

となる。ただし$C\sim 1.98$である。実際に計算するとItoに一致する。

![multiplicative.png](multiplicative.png)

## Two-step法

Two-step法を用いると、もとのLangevin方程式をStratonovichに変換することができる。

元のLangevin方程式が

$$
\dot{x} = -x^3 + x\hat{R}_1 + \hat{R}_2
$$

で与えられる時、Two-step法を適用すると、

$$
\dot{x} = -x^3 + x+ x\hat{R}_1 + \hat{R}_2
$$

に変形される。これをそのままEuler-Maruyama法で時間発展させた時の定常分布は、

* Two-step法適用前のLangevin方程式をStratonovichだと思った場合の定常分布
* Two-step法適用後のLangevin方程式をItoだと思った場合の定常分布

にそれぞれ一致する。

![twostep.png](twostep.png)

## まとめ

確率微分方程式、特にノイズが変数依存性を持つようなmultiplicative noise系にEuler-Maruyama法を適用すると、分布関数の時間発展は元のLangevin方程式をItoだと思った場合のFocker-Planck方程式に従う。Two-step法を適用すると、Ito表記で記述されたLangevin方程式がStratonovich表記に変換される。

関係を図示すると以下の通り。

![relation.png](relation.png)