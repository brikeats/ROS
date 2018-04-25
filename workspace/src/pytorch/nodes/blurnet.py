import torch
import torch.nn as nn
from torch.autograd import Variable
import numpy as np
import scipy.stats as st


def gaussian(kernlen=21, nsig=3):
    interval = (2*nsig+1.)/(kernlen)
    x = np.linspace(-nsig-interval/2., nsig+interval/2., kernlen+1)
    kern1d = np.diff(st.norm.cdf(x))
    kernel_raw = np.sqrt(np.outer(kern1d, kern1d))
    kernel = kernel_raw/kernel_raw.sum()
    return kernel


class BlurNet(nn.Module):

    def __init__(self, input_chans=3, kern_sz=11):
        super(BlurNet, self).__init__()
        self.conv = nn.Conv2d(input_chans, input_chans, kernel_size=kern_sz, padding=kern_sz/2, bias=False)
        self.conv.weight.data.zero_()
        blur_kernel = torch.from_numpy(gaussian(kern_sz))
        for chan in range(3):
            self.conv.weight.data[chan, chan, :, :] = blur_kernel

    def forward(self, x):
        return self.conv(x)

